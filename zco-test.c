
#include <zco-test.h>

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
	TestSetEnd
};

void (*TestDriverSet[]) (int) = {
	[TestSetVector] = z_vector_test,
	[TestSetString] = z_string_test,
	[TestSetMap] = z_map_test
};

void test2(int a,int b,int c,int d,int e,int f,int g,int h,int i)
{
	printf("** x = %d, %d, %d, %d, %d, %d, %d, %d, %d\n", a,b,c,d,e,f,g,h,i);
}


typedef void(*dummy)();

void dummies(dummy x) {}

void test3()
{
   dummy x = (dummy) test2;
   //volatile int x;
   
   int i;
   int *buffer = alloca(32 * sizeof(int));

   for (i=0; i<32; ++i)
	   buffer[i] = i * 10;

   asm ("movl $100,%edi\n"
        "movq $200,%rsi\n"
        "movq $300,%rdx\n"
        "movq $400,%rcx\n"
        "movq $500,%r8\n"
        "movq $600,%r9\n"
	);
   ((dummy)test2)();
}


int main(int argc, char **argv)
{
	test3();
	return;


	/* getting argument list and options */
	int c, help_wanted = 0, test_set_number = 0, test_case_number = 0;
	int option_index = 0;
	char *test_case = NULL;
	char *test_set = NULL;

	static struct option long_options[] = {
		{"test-case", 2, 0, 'c'},
		{"test-set", 2, 0, 's'},
		{"help", 0, 0, 'h'},
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
				"-s,--test-set=(vector,string,...)     test driver set (CObject class name)\n\n",
				argv[0]);

		return 0;
	}

	if (test_set) {
		/* get the test set # */
		if (!strcmp(test_set, "vector")) {
			test_set_number = TestSetVector;

		} else {
			fprintf(stderr, "Unknown test set '%s'\n", test_set);
			return -1;
		}

		/* get the test case # */
		if (test_case)
			test_case_number = atoi(test_case);
	}

	int i;

	for (i = 1; i < TestSetEnd; ++i) {
		if (test_set_number == 0 || test_set_number == i)
			TestDriverSet[i] (test_case_number);
	}

}


