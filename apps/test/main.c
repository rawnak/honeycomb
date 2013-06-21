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
#include <z-worker-group.h>

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

static void task_callback(ZBind *bind, int test_set_number, int test_case_number, int capacity)
{
        struct zco_context_t *context = CTX_FROM_OBJECT(bind);

        zco_context_set_min_segment_capacity_by_size(context, capacity);
        int i;

        for (i = 1; i < TestSetEnd; ++i) {
                if (test_set_number == 0 || test_set_number == i)
                        TestDriverSet[i](context, test_case_number);
        }

        zco_context_full_garbage_collect(context);
}

static void task_complete(ZBind *bind, int test_set_number, int test_case_number, int capacity)
{
        ZString *msg = z_string_new(CTX_FROM_OBJECT(bind), ALLOCATOR_FROM_OBJECT(bind));
        z_string_append_format(msg, "Completed test with capacity %d\n", capacity);
        char *str = z_string_get_cstring(msg, Z_STRING_ENCODING_UTF8);
        fputs(str, stdout);
        free(str);
        z_object_unref(Z_OBJECT(msg));
}

static void task_complete_with_unlock(ZBind *bind, int test_set_number, int test_case_number, int capacity, pthread_mutex_t *lock)
{
        task_complete(bind, test_set_number, test_case_number, capacity);

        pthread_mutex_unlock(lock);
}

static void application_main(ZBind *bind, int test_set_number, int test_case_number, ZWorkerGroup *worker_group, pthread_mutex_t *lock)
{
        struct zco_context_t *ctx = CTX_FROM_OBJECT(bind);
        ZMemoryAllocator *allocator = ALLOCATOR_FROM_OBJECT(bind);
        int capacity;

        is_printing = 0;

        for (capacity = 500; capacity >= 1; --capacity) {
                ZBind *task = z_bind_new(ctx, allocator);
                ZBind *completion_task = z_bind_new(ctx, allocator);

                if (is_printing) {
                        printf("Testing with minimum vector capacity of %d bytes\n"
                                        "================================================", capacity);
                        task_callback(task, test_set_number, test_case_number, capacity);
                        task_complete(completion_task, test_set_number, test_case_number, capacity);

                } else { 
                        z_bind_set_handler(task, (ZBindHandler) task_callback);
                        z_bind_append_int(task, test_set_number);
                        z_bind_append_int(task, test_case_number);
                        z_bind_append_int(task, capacity);

                        z_bind_append_int(completion_task, test_set_number);
                        z_bind_append_int(completion_task, test_case_number);
                        z_bind_append_int(completion_task, capacity);

                        if (capacity == 1) {
                                z_bind_append_ptr(completion_task, lock);
                                z_bind_set_handler(completion_task, (ZBindHandler) task_complete_with_unlock);
                        } else {
                                z_bind_set_handler(completion_task, (ZBindHandler) task_complete);
                        }

                        z_worker_group_post_task(worker_group, task, completion_task);
                }

                z_object_unref(Z_OBJECT(completion_task));
                z_object_unref(Z_OBJECT(task));
        }
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

        /* Initialize the main context */
        struct zco_context_t main_ctx;
        zco_context_init(&main_ctx);
        ZCClosureMarshal *main_marshal = z_c_closure_marshal_new(&main_ctx, main_ctx.flex_allocator);
        zco_context_set_marshal(&main_ctx, main_marshal);
        z_object_unref(Z_OBJECT(main_marshal));

        if (try_segments) {
                /* Create the application event loop */
                struct zco_context_t app_ctx;
                zco_context_init(&app_ctx);
                ZCClosureMarshal *app_marshal = z_c_closure_marshal_new(&app_ctx, app_ctx.flex_allocator);
                zco_context_set_marshal(&app_ctx, app_marshal);
                z_object_unref(Z_OBJECT(app_marshal));
                zco_context_run(&app_ctx);

                /* Create a worker group */
                ZWorkerGroup *worker_group = z_worker_group_new(&main_ctx, main_ctx.flex_allocator);
                z_worker_group_set_worker_count(worker_group, 4);

                pthread_mutex_t lock;
                pthread_mutex_init(&lock, NULL);

                /* Post all the test tasks */
                ZBind *task = z_bind_new(&main_ctx, main_ctx.flex_allocator);
                z_bind_set_handler(task, (ZBindHandler) application_main);
                z_bind_append_int(task, test_set_number);
                z_bind_append_int(task, test_case_number);
                z_bind_append_ptr(task, worker_group);
                z_bind_append_ptr(task, &lock);
                zco_context_post_task(&app_ctx, task, NULL, 0);
                z_object_unref(Z_OBJECT(task));

                /* Wait for all tests to be completed */
                pthread_mutex_lock(&lock);
                pthread_mutex_lock(&lock);

                z_object_unref(Z_OBJECT(worker_group));

                /* Destroy the application context */
                zco_context_destroy(&app_ctx);



        } else {
                int i;

                is_printing = 1;
                for (i = 1; i < TestSetEnd; ++i) {
                        if (test_set_number == 0 || test_set_number == i)
                                TestDriverSet[i](&main_ctx, test_case_number);
                }
        }

        /* Destroy the main context */
        zco_context_destroy(&main_ctx);
}


