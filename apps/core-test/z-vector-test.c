/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-vector-test.c: Vector test driver
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
#include <z-vector.h>
#include <z-vector-iter.h>
#include <stdio.h>
#include <assert.h>

static void case1(struct zco_context_t *context)
{
	/* Testing z_vector_begin */
	ZVector *vec;
	ZVectorIter *it, *end;
	int i;

	trace("======================\n");
	trace("Vector case #1:\n");

	vec = z_vector_new(context, NULL);
        z_vector_set_item_size(vec, sizeof(int));

	for (i = 1; i <= 5; ++i) {
		z_vector_push_back(vec, &i);
	}

	it = z_vector_get_begin(vec);
	end = z_vector_get_end(vec);

	trace("vec contains:");

	for (i = 1; !z_vector_iter_is_equal(it, end); z_vector_iter_increment(it), ++i) {

		int x = *((int *)z_vector_get_item(vec, it));
		trace(" %d", x);
		assert(i == x);
	}

	trace("\n\n");

	z_object_unref(Z_OBJECT(vec));
	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(end));
}

static void case2(struct zco_context_t *context)
{
	/* Testing z_vector_get_size */
	ZVector *vec;
	ZVectorIter *end;
	int i, size;

	trace("======================\n");
	trace("Vector case #2:\n");

	vec = z_vector_new(context, NULL);
        z_vector_set_item_size(vec, sizeof(int));

	/* size == 0 */
	size = z_vector_get_size(vec);
	trace("0. size: %d\n", size);

	assert(size == 0);

	/* size == 10 */
	for (i = 1; i <= 10; ++i) {
		z_vector_push_back(vec, &i);
	}

	size = z_vector_get_size(vec);
	trace("1. size: %d\n", size);

	assert(size == 10);

	/* size == 20 */
	int x = 100;
	end = z_vector_get_end(vec);
	z_vector_insert(vec, end, 10, &x);

	size = z_vector_get_size(vec);
	trace("2. size: %d\n", size);

	assert(size == 20);

	/* size == 19 */
	z_vector_pop_back(vec, NULL);

	size = z_vector_get_size(vec);
	trace("3. size: %d\n", size);

	assert(size == 19);

	z_object_unref(Z_OBJECT(vec));
	z_object_unref(Z_OBJECT(end));
}

static void case3_helper1(void *data, void *userdata)
{
	*((int *)data) = 100;
}

static void case3(struct zco_context_t *context)
{
	/* Testing z_vector_set_size */
	ZVector *vec;
	ZVectorIter *it;
	int i;

	trace("======================\n");
	trace("Vector case #3:\n");

	vec = z_vector_new(context, NULL);
        z_vector_set_item_size(vec, sizeof(int));
	z_vector_set_item_construct(vec, case3_helper1);

	for (i = 1; i <= 10; ++i) {
		z_vector_push_back(vec, &i);
	}

	z_vector_set_size(vec, 5);
	z_vector_set_size(vec, 12);

	trace("vec contains:");
	int size = z_vector_get_size(vec);

        it = z_vector_get_begin(vec);

	for (i = 0; i < size; ++i) {
		int x = *((int *) z_vector_get_item(vec, it));
		z_vector_iter_increment(it);

		trace(" %d", x);
		assert((i < 5 && x == i + 1) || (i >= 5 && x == 100));
	}

	trace("\n\n");

	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(vec));
}

static void case4(struct zco_context_t *context)
{
	/* Testing z_vector_is_empty */
	ZVector *vec;
	int i, sum = 0;

	trace("======================\n");
	trace("Vector case #4:\n");

	vec = z_vector_new(context, NULL);
        z_vector_set_item_size(vec, sizeof(int));

	for (i = 1; i <= 10; ++i) {
		z_vector_push_back(vec, &i);
	}

	while (!z_vector_get_is_empty(vec)) {
		sum += *((int *)z_vector_get_back(vec));
		z_vector_pop_back(vec, NULL);
	}

	assert(sum == 55);
	trace("total: %d\n\n", sum);

	z_object_unref(Z_OBJECT(vec));
}

static void case5_helper1(void *data, void *userdata)
{
	*((int *)data) = 0;
}

static void case5(struct zco_context_t *context)
{
	/* Testing z_vector_get_item / z_vector_set_item */
	ZVector *vec;
	ZVectorIter *it;
	int i;

	trace("======================\n");
	trace("Vector case #5:\n");

	vec = z_vector_new(context, NULL);
        z_vector_set_item_size(vec, sizeof(int));
	z_vector_set_item_construct(vec, case5_helper1);
	z_vector_set_size(vec, 10);

        it = z_vector_get_begin(vec);

	for (i = 0; i < z_vector_get_size(vec); ++i) {
		z_vector_set_item(vec, it, &i);
		z_vector_iter_increment(it);
	}

	trace("vec contains:");
	z_vector_iter_set_absolute_index(it, 0);

	for (i = 0; i < z_vector_get_size(vec); ++i) {
		int x = *((int *) z_vector_get_item(vec, it));
		z_vector_iter_increment(it);

		trace(" %d", x);
		assert(x == i);
	}

	trace("\n\n");

	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(vec));
}

static void case6(struct zco_context_t *context)
{
	/* Testing z_vector_get_front / z_vector_set_front */
	ZVector *vec;
	int x;

	trace("======================\n");
	trace("Vector case #6:\n");

	vec = z_vector_new(context, NULL);
        z_vector_set_item_size(vec, sizeof(int));

	x = 77;
	z_vector_push_back(vec, &x);

	x = 16;
	z_vector_push_back(vec, &x);

	x = *((int *)z_vector_get_front(vec)) - *((int *)z_vector_get_back(vec));
	z_vector_set_front(vec, &x);

	x = *((int *)z_vector_get_front(vec));
	trace("vec front is now %d\n\n", x);
	assert(x == 61);

	z_object_unref(Z_OBJECT(vec));
}

static void case7(struct zco_context_t *context)
{
	/* Testing z_vector_get_back / z_vector_set_back */
	ZVector *vec;
	ZVectorIter *it;
	int i, x;

	trace("======================\n");
	trace("Vector case #7:\n");

	vec = z_vector_new(context, NULL);
        z_vector_set_item_size(vec, sizeof(int));

	x = 10;
	z_vector_push_back(vec, &x);

	while (*((int *)z_vector_get_back(vec)) != 0) {
		x = *((int *)z_vector_get_back(vec)) - 1;
		z_vector_push_back(vec, &x);
	}

        it = z_vector_get_begin(vec);
	for (i = 0; i < z_vector_get_size(vec); ++i) {

		int x = *((int *)z_vector_get_item(vec, it));
		z_vector_iter_increment(it);
		trace(" %d", x);

		assert(x == (10 - i));
	}

	trace("\n\n");

	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(vec));
}

static void case8(struct zco_context_t *context)
{
	/* Testing z_vector_push_back / z_vector_pop_back */
	ZVector *vec;
	int x, sum = 0;

	trace("======================\n");
	trace("Vector case #8:\n");

	vec = z_vector_new(context, NULL);
        z_vector_set_item_size(vec, sizeof(int));

	x = 100;
	z_vector_push_back(vec, &x);

	x = 200;
	z_vector_push_back(vec, &x);

	x = 300;
	z_vector_push_back(vec, &x);

	while (!z_vector_get_is_empty(vec)) {
		sum += *((int *)z_vector_get_back(vec));
		z_vector_pop_back(vec, NULL);
	}

	z_object_unref(Z_OBJECT(vec));
	trace("The elements of vec summed %d\n\n", sum);

	assert(sum == 600);
}

static void case9_helper1(void *data, void *userdata)
{
	*((int *)data) = 100;
}

static void case9_helper2(void *data, void *userdata)
{
	*((int *)data) = 400;
}

static void case9(struct zco_context_t *context)
{
	/* Testing z_vector_insert / z_vector_insert_range */

	ZVector *vec1, *vec2;
	ZVectorIter *it, *begin, *end;
	int x, i;

	trace("======================\n");
	trace("Vector case #9:\n");

	vec1 = z_vector_new(context, NULL);
        z_vector_set_item_size(vec1, sizeof(int));
	z_vector_set_item_construct(vec1, case9_helper1);
	z_vector_set_size(vec1, 3);

	x = 200;
	it = z_vector_get_begin(vec1);
	z_vector_insert(vec1, it, 1, &x);
	z_object_unref(Z_OBJECT(it));

	x = 300;
	it = z_vector_get_begin(vec1);
	z_vector_insert(vec1, it, 2, &x);
	z_object_unref(Z_OBJECT(it));

	vec2 = z_vector_new(context, NULL);
        z_vector_set_item_size(vec2, sizeof(int));
	z_vector_set_item_construct(vec2, case9_helper2);
	z_vector_set_size(vec2, 2);

	it = z_vector_get_begin(vec1);
	z_vector_iter_advance(it, 2);

	begin = z_vector_get_begin(vec2);
	end = z_vector_get_end(vec2);
	
	z_vector_insert_range(vec1, it, vec2, begin, end);
	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(begin));
	z_object_unref(Z_OBJECT(end));

	trace("vec1 contains:");

	it = z_vector_get_begin(vec1);
	end = z_vector_get_end(vec1);

	for (i = 0; !z_vector_iter_is_equal(it, end); z_vector_iter_increment(it), ++i) {
		int x = *((int *)z_vector_get_item(vec1, it));

		trace(" %d", x);

		assert((i >= 0 && i <= 1 && x == 300)
			|| (i >= 2 && i <= 3 && x == 400) || (i == 4 && x == 200)
			|| (i >= 5 && i <= 7 && x == 100));
	}

	trace("\n\n");

	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(end));
	z_object_unref(Z_OBJECT(vec1));
	z_object_unref(Z_OBJECT(vec2));
}

static void case10(struct zco_context_t *context)
{
	/* Testing z_vector_erase */
	int i;
	ZVector *vec;
	ZVectorIter *it, *start, *end;

	trace("======================\n");
	trace("Vector case #10:\n");

	vec = z_vector_new(context, NULL);
        z_vector_set_item_size(vec, sizeof(int));

	for (i = 1; i <= 10; ++i) {
		z_vector_push_back(vec, &i);
	}

	start = z_vector_get_begin(vec);
	z_vector_iter_advance(start, 5);

	end = z_vector_iter_dup(start);
	z_vector_iter_increment(end);

	z_vector_erase(vec, start, end);
	z_object_unref(Z_OBJECT(start));
	z_object_unref(Z_OBJECT(end));

	start = z_vector_get_begin(vec);
	end = z_vector_iter_dup(start);

	z_vector_iter_advance(end, 3);
	z_vector_erase(vec, start, end);
	z_object_unref(Z_OBJECT(start));
	z_object_unref(Z_OBJECT(end));

	trace("vec contains:");
        it = z_vector_get_begin(vec);

	for (i = 0; i < z_vector_get_size(vec); ++i) {
		int x = *((int *)z_vector_get_item(vec, it));
		z_vector_iter_increment(it);

		trace(" %d", x);

		assert((i < 2 && i + 4 == x) || (i < 6 && i + 5 == x));
	}

	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(vec));

	trace("\n\n");
}

static void case11(struct zco_context_t *context)
{
	/* Testing z_vector_clear */
	int i, x;
	ZVector *vec;
	ZVectorIter *it;

	trace("======================\n");
	trace("Vector case #11:\n");

	vec = z_vector_new(context, NULL);
        z_vector_set_item_size(vec, sizeof(int));

	x = 100;
	z_vector_push_back(vec, &x);

	x = 200;
	z_vector_push_back(vec, &x);

	x = 300;
	z_vector_push_back(vec, &x);

	trace("vec contains:");
        it = z_vector_get_begin(vec);

	for (i = 0; i < z_vector_get_size(vec); ++i) {
		int x = *((int *)z_vector_get_item(vec, it));
		z_vector_iter_increment(it);

		trace(" %d", x);
		assert((i + 1) * 100 == x);
	}

	z_object_unref(Z_OBJECT(it));
	z_vector_clear(vec);

	x = 1101;
	z_vector_push_back(vec, &x);

	x = 2202;
	z_vector_push_back(vec, &x);

	trace("\nmyvector contains:");
        it = z_vector_get_begin(vec);

	for (i = 0; i < z_vector_get_size(vec); ++i) {
		int x = *((int *)z_vector_get_item(vec, it));
		z_vector_iter_increment(it);

		trace(" %d", x);
		assert((i + 1) * 1101 == x);
	}

	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(vec));

	trace("\n\n");
}

void z_vector_test(struct zco_context_t *context, int id)
{
	DEFINE_TEST(1, case1, context);
	DEFINE_TEST(2, case2, context);
	DEFINE_TEST(3, case3, context);
	DEFINE_TEST(4, case4, context);
	DEFINE_TEST(5, case5, context);
	DEFINE_TEST(6, case6, context);
	DEFINE_TEST(7, case7, context);
	DEFINE_TEST(8, case8, context);
	DEFINE_TEST(9, case9, context);
	DEFINE_TEST(10, case10, context);
	DEFINE_TEST(11, case11, context);
}

