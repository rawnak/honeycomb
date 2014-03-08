/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * main.c: Toolkit test main
 * This file is part of ZCO.
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ZCO is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with ZCO.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <zco-context.h>
#include <zco-toolkit-test.h>
#include <z-string.h>
#include <zco-context.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdarg.h>
#include <assert.h>

enum TestSet {
	TestSetString = 1,
	TestSetInt32 = 2,
	TestSetEnd
};

void (*TestDriverSet[]) (struct zco_context_t *, int) = {
	[TestSetString] = ztk_string_test,
	[TestSetInt32] = ztk_int32_test
};

int is_verbose;

void trace(const char *fmt, ...)
{
        va_list ap;
        va_start(ap, fmt);
        vprintf(fmt, ap);
        va_end(ap);
}

ZString *read_from_fd(struct zco_context_t *ctx, ZMemoryAllocator *alloc, int fd)
{
        ZString *out = z_string_new(ctx, alloc);
        unsigned char buf[1024];
        int count;

        while ((count = read(fd, buf, sizeof(buf)))) {
                if (count < 0) {
                        perror("read");
                        abort();
                }

                buf[count] = 0;
                z_string_append_cstring(out, buf, Z_STRING_ENCODING_UTF8);
        }

        return out;
}

int write_stdout_to_pipe(int fd)
{
        int original_stdout = dup(1);
        dup2(fd, 1);
        close(fd);

        return original_stdout;
}

void restore_stdout(int original_stdout)
{
        dup2(original_stdout, 1);
        close(original_stdout);
}

void verify_output(ZRuntimeContext *runtime_context, ZString *expected_value)
{
        pid_t pid;

        /* create a full-duplex pipe */
        int pipe_to_child[2];
        int pipe_to_parent[2];

        pipe(pipe_to_child);
        pipe(pipe_to_parent);

        switch (pid = fork())
        {
        case -1:
                perror("fork");
                abort();
                break;

        case 0:  /* child */
                close(pipe_to_child[1]);
                close(pipe_to_parent[0]);
                dup2(pipe_to_child[0], 0);
                dup2(pipe_to_parent[1], 1);
                execlp("node", "node", NULL);
                break;
        }

        close(pipe_to_child[0]);
        close(pipe_to_parent[1]);

        if (is_verbose) {
                /* print out the script if we are in verbose mode */
                z_runtime_context_run(runtime_context);
        }

        /* backup the original stdout and redirect stdout to 'pipe_to_child' */
        int original_stdout = write_stdout_to_pipe(pipe_to_child[1]);

        /* push the script to stdout, which is the pipe to the child */
        z_runtime_context_run(runtime_context);
        z_runtime_context_clear(runtime_context);

        /* restore the original stdout */
        restore_stdout(original_stdout);

        /* wait for child to exit */
        siginfo_t info;
        memset (&info, 0, sizeof(info));
        waitid (P_PID, pid, &info, WEXITED | WUNTRACED | WNOHANG | WNOWAIT);

        /* read all data from pipe_to_parent[0] and store it in a string */
        ZString *out = read_from_fd(CTX_FROM_OBJECT(runtime_context), ALLOCATOR_FROM_OBJECT(runtime_context), pipe_to_parent[0]);
        close(pipe_to_parent[0]);

        /* compare the output matches the expected value */
        if (z_string_compare(out, NULL, expected_value, NULL, 0, -1)) {
                char *s;

                s = z_string_get_cstring(expected_value, Z_STRING_ENCODING_UTF8);
                printf("Expected value: \n'%s'\n", s);
                free(s);

                s = z_string_get_cstring(out, Z_STRING_ENCODING_UTF8);
                printf("\nActual value: \n'%s'\n", s);
                free(s);

                abort();
        }

        z_object_unref(Z_OBJECT(out));
}

void define_test(void(*callback)(ZRuntimeContext *), struct zco_context_t *ctx, const char *title)
{
	trace("======================\n");
	trace("%s:\n", title);

        /* redirect stdout to a pipe */
        int the_pipe[2];
        pipe(the_pipe);
        int original_stdout = write_stdout_to_pipe(the_pipe[1]);

        /* run test in native mode */
        ZRuntimeContext *runtime_context = z_runtime_context_new(ctx, NULL);
        z_runtime_context_set_target(runtime_context, 0);
        callback(runtime_context);

        /* restore stdout as we don't need any more data that is sent to it */
        restore_stdout(original_stdout);

        /* read data that is sent to the pipe and close the pipe */
        ZString *out = read_from_fd(ctx, NULL, the_pipe[0]);
        close(the_pipe[0]);
        z_object_unref(Z_OBJECT(runtime_context));

        /* run test in JS mode and verify its output */
        runtime_context = z_runtime_context_new(ctx, NULL);
        z_runtime_context_set_target(runtime_context, 1);
        callback(runtime_context);
        verify_output(runtime_context, out);
        z_object_unref(Z_OBJECT(runtime_context));

        /* print out the expected string */
        char *print_out = z_string_get_cstring(out, Z_STRING_ENCODING_UTF8);
        fputs(print_out, stdout);
        free(print_out);

        z_object_unref(Z_OBJECT(out));
        trace("\n");
}

int main(int argc, char **argv)
{
	/* getting argument list and options */
	int c, help_wanted = 0, test_set_number = 0, test_case_number = 0;
	int option_index = 0;
	char *test_case = NULL;
	char *test_set = NULL;

	static struct option long_options[] = {
		{"test-case", 2, 0, 'c'},
		{"test-set", 2, 0, 's'},
		{"help", 0, 0, 'h'},
                {"full", 0, 0, 'f'},
		{0, 0, 0, 0}
	};

	/* disables default getopt warnings */
	opterr = 0;
        is_verbose = 0;

	while ((c = getopt_long(argc, argv, "c:s:h:v", long_options, &option_index)) != -1) {
		switch (c) {
		case 'c':
			test_case = optarg;
			break;

		case 's':
			test_set = optarg;
			break;

		case 'h':
			help_wanted = 1;
			break;

                case 'v':
                        is_verbose = 1;
                        break;

		case '?':
			if (optopt == 'c')
				fprintf(stderr, "Option -%c requires an argument.\n", optopt);

			else if (isprint(optopt))
				fprintf(stderr, "Unknown option -%c.\n", optopt);

			else
				fprintf(stderr, "Unknown option character \\x%x.\n", optopt);

		default:
			return 1;
		}
	}

	if (help_wanted) {
		fprintf(stderr,
				"Usage: %s [OPTION]...\n"
				"Runs the test driver for the specific test case for the test driver set\n\n"
				"-c,--test-case=#                      test case number within the test driver set\n"
				"-s,--test-set=(vector,string,...)     test driver set (ZObject class name)\n"
                                "-f,--full                             test a large number of segment sizes\n\n",
				argv[0]);

		return 0;
	}

	if (test_set) {
		/* get the test set # */
                if (!strcmp(test_set, "string")) {
                        test_set_number = TestSetString;

                } else if (!strcmp(test_set, "int32")) {
                        test_set_number = TestSetInt32;

		} else {
			fprintf(stderr, "Unknown test set '%s'\n", test_set);
			return -1;
		}

		/* get the test case # */
		if (test_case)
			test_case_number = atoi(test_case);
	}

        /* Initialize the main context */
        struct zco_context_t main_ctx;
        zco_context_init(&main_ctx);

        int i;
        for (i = 1; i < TestSetEnd; ++i) {
                if (test_set_number == 0 || test_set_number == i) {
                        TestDriverSet[i](&main_ctx, test_case_number);
                }
        }

        /* Destroy the main context */
        zco_context_destroy(&main_ctx);
}


