#include <zco-test.h>
#include <z-vector.h>
#include <z-vector-iter.h>
#include <stdio.h>
#include <assert.h>

static struct zco_context_t context;

static void case1(void)
{
	/* Testing z_vector_begin */
	ZVector *vec;
	ZVectorIter *it, *end;
	int i;

	printf("======================\n");
	printf("Vector case #1:\n");

	vec = z_vector_new(&context, sizeof(int));

	for (i = 1; i <= 5; ++i) {
		z_vector_push_back(vec, &i);
	}

	it = z_vector_get_begin(vec);
	end = z_vector_get_end(vec);

	printf("vec contains:");

	for (i = 1; !z_vector_iter_is_equal(it, end); z_vector_iter_increment(it), ++i) {

		int x = *((int *)z_vector_get_item(vec, it));
		printf(" %d", x);
		assert(i == x);
	}

	printf("\n\n");

	z_object_unref(Z_OBJECT(vec));
}



void z_vector_test(int id)
{
	zco_context_init(&context);
	DEFINE_TEST(1, case1);
}

