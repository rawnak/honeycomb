/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * zco-test.c: Test driver main
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


#include <zco-test.h>
#include <z-bind.h>
#include <z-c-closure-marshal.h>
#include <z-event-loop.h>
#include <z-string.h>

#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdarg.h>

enum TestSet {
	TestSetVector = 1,
	TestSetString,
	TestSetMap,
	TestSetSignal,
	TestSetEnd
};

void (*TestDriverSet[]) (struct zco_context_t *, int) = {
	[TestSetVector] = z_vector_test,
	[TestSetString] = z_string_test,
	[TestSetMap] = z_map_test,
	[TestSetSignal] = signal_test
};

int is_printing;

void trace(const char *fmt, ...)
{
        va_list ap;

        if (!is_printing)
                return;

        va_start(ap, fmt);
        vprintf(fmt, ap);
        va_end(ap);
}

void task_callback(ZBind *bind, int test_set_number, int test_case_number, int capacity)
{
        struct zco_context_t *context = CTX_FROM_OBJECT(bind);

        zco_context_set_min_segment_capacity_by_size(context, capacity);
        int i;

        for (i = 1; i < TestSetEnd; ++i) {
                if (test_set_number == 0 || test_set_number == i)
                        TestDriverSet[i](context, test_case_number);
        }

        zco_context_full_garbage_collect(context);

        ZString *msg = z_string_new(context, ALLOCATOR_FROM_OBJECT(bind));
        z_string_append_format(msg, "Completed test with capacity %d\n", capacity);
        char *str = z_string_get_cstring(msg, Z_STRING_ENCODING_UTF8);
        fputs(str, stdout);
        free(str);
        z_object_unref(Z_OBJECT(msg));
}

int main(int argc, char **argv)
{
	/* getting argument list and options */
	int c, help_wanted = 0, test_set_number = 0, test_case_number = 0, try_segments = 0;
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

	while ((c = getopt_long(argc, argv, "c:s:h", long_options, &option_index)) != -1) {
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

                case 'f':
                        try_segments = 1;
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
				"-s,--test-set=(vector,string,...)     test driver set (CObject class name)\n"
                                "-f,--full                             test a large number of segment sizes\n\n",
				argv[0]);

		return 0;
	}

	if (test_set) {
		/* get the test set # */
		if (!strcmp(test_set, "vector")) {
			test_set_number = TestSetVector;

                } else if (!strcmp(test_set, "string")) {
                        test_set_number = TestSetString;

                } else if (!strcmp(test_set, "map")) {
                        test_set_number = TestSetMap;

                } else if (!strcmp(test_set, "signal")) {
                        test_set_number = TestSetSignal;

		} else {
			fprintf(stderr, "Unknown test set '%s'\n", test_set);
			return -1;
		}

		/* get the test case # */
		if (test_case)
			test_case_number = atoi(test_case);
	}

        int capacity;
	int i;

        if (try_segments) {
                struct zco_context_t main_ctx;
                struct zco_context_t *contexts;
                int n_threads = 8;
                int count = 0;
                int i;

                /* Initialize the main context */
                zco_context_init(&main_ctx);
                ZCClosureMarshal *marshal = z_c_closure_marshal_new(&main_ctx, NULL);
                zco_context_set_marshal(&main_ctx, marshal);
                z_object_unref(Z_OBJECT(marshal));

                /* Initialize worker contexts */
                contexts = malloc(sizeof(struct zco_context_t) * n_threads);
                for (i=0; i<n_threads; ++i) {
                        ZCClosureMarshal *marshal;

                        zco_context_init(contexts+i);
                        marshal = z_c_closure_marshal_new(contexts+i, NULL);
                        zco_context_set_marshal(contexts+i, marshal);
                        z_object_unref(Z_OBJECT(marshal));

                        zco_context_run(contexts+i);
                }

                is_printing = 0;
                for (capacity = 500; capacity >= 1; --capacity) {
                        ZBind *task = z_bind_new(&main_ctx, NULL);

                        if (is_printing) {
                                printf("Testing with minimum vector capacity of %d bytes\n"
                                       "================================================", capacity);
                                task_callback(task, test_set_number, test_case_number, capacity);

                        } else { 
                                z_bind_set_handler(task, (ZBindHandler) task_callback);
                                z_bind_append_int(task, test_set_number);
                                z_bind_append_int(task, test_case_number);
                                z_bind_append_int(task, capacity);

                                zco_context_post_task(contexts + (count % n_threads), task, 0);

                                z_object_unref(Z_OBJECT(task));
                                ++count;
                        }
                }

                /* Notify all worker contexts that we are ready to terminate */ 
                for (i=0; i<n_threads; ++i) 
                        zco_context_prepare_destroy(contexts+i);

                /* Destroy the worker contexts */
                for (i=0; i<n_threads; ++i) 
                        zco_context_destroy(contexts+i);

                free(contexts);

                /* Destroy the main context */
                zco_context_destroy(&main_ctx);

        } else {
                struct zco_context_t context;
                zco_context_init(&context);

                is_printing = 1;
                for (i = 1; i < TestSetEnd; ++i) {
                        if (test_set_number == 0 || test_set_number == i)
                                TestDriverSet[i](&context, test_case_number);
                }

                zco_context_destroy(&context);
        }
}


