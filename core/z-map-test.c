/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-map-test.c: Map test driver
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
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <z-map.h>
#include <z-map-iter.h>
#include <z-string.h>
#include <z-string-iter.h>

#define INT_TO_PTR(x) ((void *) ((unsigned long) (x)))
#define PTR_TO_INT(x) ((int64_t) ((long) (x)))

static struct zco_context_t context;

static int map_compare(ZMap *self, const void *a, const void *b)
{
	return z_string_compare((ZString *) a, NULL, (ZString *) b, NULL, 0, -1);
}

static void case1(void)
{
	/* Testing z_map_get_begin / z_map_get_end */
	ZMap *mymap;
	ZMapIter *it, *end;
	ZString *key;
	int test_result[3] = { 200, 100, 300 };
	int i;

	printf("======================\n");
	printf("ZMap case #1:\n");

	mymap = z_map_new(&context);

	z_map_set_key_destruct(mymap, (ZMapItemCallback) z_object_unref);
	z_map_set_compare(mymap, map_compare);

	key = z_string_new(&context);
	z_string_set_cstring(key, "b", Z_STRING_ENCODING_UTF8);
	z_map_assign(mymap, key, INT_TO_PTR(100));

	key = z_string_new(&context);
	z_string_set_cstring(key, "a", Z_STRING_ENCODING_UTF8);
	z_map_assign(mymap, key, INT_TO_PTR(200));

	key = z_string_new(&context);
	z_string_set_cstring(key, "c", Z_STRING_ENCODING_UTF8);
	z_map_assign(mymap, key, INT_TO_PTR(300));

	it = z_map_get_begin(mymap);
	end = z_map_get_end(mymap);

	printf("mymap contains:");

	for (i = 0; !z_map_iter_is_equal(it, end); z_map_iter_increment(it), ++i) {
		int x = PTR_TO_INT(z_map_get_value(mymap, it));
		printf(" %d", x);
		assert(test_result[i] == x);
	}

	printf("\n\n");
	z_object_unref(Z_OBJECT(mymap));
}

static void case2(void)
{
	/* Testing z_map_is_empty */
	ZMap *mymap;
	ZString *key;
	ZString *test_key[3];
	int test_value[3] = { 10, 20, 30 };
	int i;

	printf("======================\n");
	printf("ZMap case #2:\n");

	mymap = z_map_new(&context);
	z_map_set_key_destruct(mymap, (ZMapItemCallback) z_object_unref);
	z_map_set_compare(mymap, map_compare);

	key = z_string_new(&context);
	z_string_set_cstring(key, "a", Z_STRING_ENCODING_UTF8);
	z_map_assign(mymap, key, INT_TO_PTR(10));

	key = z_string_new(&context);
	z_string_set_cstring(key, "b", Z_STRING_ENCODING_UTF8);
	z_map_assign(mymap, key, INT_TO_PTR(20));

	key = z_string_new(&context);
	z_string_set_cstring(key, "c", Z_STRING_ENCODING_UTF8);
	z_map_assign(mymap, key, INT_TO_PTR(30));

	printf("mymap contains:\n");

	/* create the test key strings */
	test_key[0] = z_string_new(&context);
	test_key[1] = z_string_new(&context);
	test_key[2] = z_string_new(&context);

	z_string_set_cstring(test_key[0], "a", Z_STRING_ENCODING_UTF8);
	z_string_set_cstring(test_key[1], "b", Z_STRING_ENCODING_UTF8);
	z_string_set_cstring(test_key[2], "c", Z_STRING_ENCODING_UTF8);

	i = 0;

	while (!z_map_get_is_empty(mymap)) {
		ZMapIter *first, *second;
		ZString *key;
		char *raw_key;
		int value;

		first = z_map_get_begin(mymap);
		second = z_map_iter_dup(first);
		z_map_iter_increment(second);

		key = Z_STRING(z_map_get_key(mymap, first));
		raw_key = z_string_get_cstring(key, Z_STRING_ENCODING_UTF8);
		value = PTR_TO_INT(z_map_get_value(mymap, first));

		printf("\tkey: %s, value: %d\n", raw_key, value);
		free(raw_key);

		assert(z_string_compare(key, NULL, test_key[i], NULL, 0, -1) == 0);
		assert(value == test_value[i]);

		z_map_erase(mymap, first, second);
		++i;
	}

	printf("\n\n");
	z_object_unref(Z_OBJECT(mymap));
}

static void case3(void)
{
	/* Testing z_map_get_size */
	ZMap *mymap;
	ZString *key;
	int size;

	printf("======================\n");
	printf("ZMap case #3:\n");

	mymap = z_map_new(&context);
	z_map_set_key_destruct(mymap, (ZMapItemCallback) z_object_unref);

	z_map_set_compare(mymap, map_compare);

	key = z_string_new(&context);
	z_string_set_cstring(key, "a", Z_STRING_ENCODING_UTF8);
	z_map_assign(mymap, key, INT_TO_PTR(101));

	key = z_string_new(&context);
	z_string_set_cstring(key, "b", Z_STRING_ENCODING_UTF8);
	z_map_assign(mymap, key, INT_TO_PTR(202));

	key = z_string_new(&context);
	z_string_set_cstring(key, "c", Z_STRING_ENCODING_UTF8);
	z_map_assign(mymap, key, INT_TO_PTR(302));

	size = z_map_get_size(mymap);
	printf("mymap size = %d\n", size);
	assert(size == 3);

	z_object_unref(Z_OBJECT(mymap));
}

static void case4(void)
{
	/* Testing z_map_find / z_map_assign */
	ZMap *mymap;
	ZString *key1, *key2, *key3, *key4, *value;
	ZString *test_value1, *test_value2;
	ZMapIter *it;
	char *raw_str;
	int size, found;

	printf("======================\n");
	printf("ZMap case #4:\n");

	mymap = z_map_new(&context);
	z_map_set_key_destruct(mymap, (ZMapItemCallback) z_object_unref);
	z_map_set_value_destruct(mymap, (ZMapItemCallback) z_object_unref);

	z_map_set_compare(mymap, map_compare);

	/* first element */
	key1 = z_string_new(&context);
	z_string_set_cstring(key1, "a", Z_STRING_ENCODING_UTF8);

	value = z_string_new(&context);
	z_string_set_cstring(value, "an element", Z_STRING_ENCODING_UTF8);
	z_map_assign(mymap, key1, value);

	/* second element */
	key2 = z_string_new(&context);
	z_string_set_cstring(key2, "b", Z_STRING_ENCODING_UTF8);

	value = z_string_new(&context);
	z_string_set_cstring(value, "another element", Z_STRING_ENCODING_UTF8);
	z_map_assign(mymap, key2, value);

	/* third element */
	key3 = z_string_new(&context);
	z_string_set_cstring(key3, "c", Z_STRING_ENCODING_UTF8);

	it = z_map_find(mymap, key2);
	assert(it != NULL);

	value = z_string_dup(z_map_get_value(mymap, it));
	z_object_unref(Z_OBJECT(it));
	z_map_assign(mymap, key3, value);

	key4 = z_string_new(&context);
	z_string_set_cstring(key4, "d", Z_STRING_ENCODING_UTF8);

	/* create test strings */
	test_value1 = z_string_new(&context);
	z_string_set_cstring(test_value1, "an element", Z_STRING_ENCODING_UTF8);

	test_value2 = z_string_new(&context);
	z_string_set_cstring(test_value2, "another element", Z_STRING_ENCODING_UTF8);

	/* print mymap['a'] */
	it = z_map_find(mymap, key1);
	assert(it != NULL);
	value = z_map_get_value(mymap, it);
	z_object_unref(Z_OBJECT(it));
	assert(z_string_compare(value, NULL, test_value1, NULL, 0, -1) == 0);

	if (value) {
		raw_str = z_string_get_cstring(value, Z_STRING_ENCODING_UTF8);
		printf("mymap['a'] = %s\n", raw_str);
		free(raw_str);
	} else {
		printf("mymap['a'] = undefined\n");
	}

	/* print mymap['b'] */
	it = z_map_find(mymap, key2);
	assert(it != NULL);
	value = z_map_get_value(mymap, it);
	z_object_unref(Z_OBJECT(it));
	assert(z_string_compare(value, NULL, test_value2, NULL, 0, -1) == 0);

	if (value) {
		raw_str = z_string_get_cstring(value, Z_STRING_ENCODING_UTF8);
		printf("mymap['b'] = %s\n", raw_str);
		free(raw_str);
	} else {
		printf("mymap['b'] = undefined\n");
	}

	/* print mymap['c'] */
	it = z_map_find(mymap, key3);
	assert(it != NULL);
	value = z_map_get_value(mymap, it);
	z_object_unref(Z_OBJECT(it));
	assert(z_string_compare(value, NULL, test_value2, NULL, 0, -1) == 0);

	if (value) {
		raw_str = z_string_get_cstring(value, Z_STRING_ENCODING_UTF8);
		printf("mymap['c'] = %s\n", raw_str);
		free(raw_str);
	} else {
		printf("mymap['c'] = undefined\n");
	}

	/* print mymap['d'] */
	it = z_map_find(mymap, key4);
	assert(it == NULL);
	printf("mymap['d'] = (none)\n");

	size = z_map_get_size(mymap);
	printf("mymap size = %d\n", size);
	assert(size == 3);

	z_object_unref(Z_OBJECT(mymap));
	z_object_unref(Z_OBJECT(test_value1));
	z_object_unref(Z_OBJECT(test_value2));
	z_object_unref(Z_OBJECT(key4));
}

static void case5(void)
{
	/* Testing z_map_insert */
	ZMap *mymap;
	ZMapIter *it, *end;
	ZString *key;
	int test_result[4] = { 100, 300, 400, 200 };
	int i;

	printf("======================\n");
	printf("ZMap case #5:\n");

	mymap = z_map_new(&context);
	z_map_set_key_destruct(mymap, (ZMapItemCallback) z_object_unref);
	z_map_set_compare(mymap, map_compare);

	key = z_string_new(&context);
	z_string_set_cstring(key, "a", Z_STRING_ENCODING_UTF8);
	assert(z_map_insert(mymap, key, INT_TO_PTR(100)) == 0);

	key = z_string_new(&context);
	z_string_set_cstring(key, "z", Z_STRING_ENCODING_UTF8);
	assert(z_map_insert(mymap, key, INT_TO_PTR(200)) == 0);

	key = z_string_new(&context);
	z_string_set_cstring(key, "z", Z_STRING_ENCODING_UTF8);
	assert(z_map_insert(mymap, key, INT_TO_PTR(500)) == -1);

	key = z_string_new(&context);
	z_string_set_cstring(key, "b", Z_STRING_ENCODING_UTF8);
	assert(z_map_insert(mymap, key, INT_TO_PTR(300)) == 0);

	key = z_string_new(&context);
	z_string_set_cstring(key, "c", Z_STRING_ENCODING_UTF8);
	assert(z_map_insert(mymap, key, INT_TO_PTR(400)) == 0);

	it = z_map_get_begin(mymap);
	end = z_map_get_end(mymap);

	printf("mymap contains:");

	for (i = 0; !z_map_iter_is_equal(it, end); z_map_iter_increment(it), ++i) {
		int x = PTR_TO_INT(z_map_get_value(mymap, it));
		printf(" %d", x);
		assert(test_result[i] == x);
	}

	printf("\n\n");
	z_object_unref(Z_OBJECT(mymap));
	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(end));
}

static void case6(void)
{
	/* Testing z_map_erase */
	ZMap *mymap;
	ZMapIter *it, *end;
	ZString *key1, *key2, *key3, *key4, *key5, *key6;
	int test_result[2] = { 10, 40 };
	int i;

	printf("======================\n");
	printf("ZMap case #6:\n");

	mymap = z_map_new(&context);
	z_map_set_key_destruct(mymap, (ZMapItemCallback) z_object_unref);

	z_map_set_compare(mymap, map_compare);

	key1 = z_string_new(&context);
	z_string_set_cstring(key1, "a", Z_STRING_ENCODING_UTF8);
	z_map_assign(mymap, key1, INT_TO_PTR(10));

	key2 = z_string_new(&context);
	z_string_set_cstring(key2, "b", Z_STRING_ENCODING_UTF8);
	z_map_assign(mymap, key2, INT_TO_PTR(20));

	key3 = z_string_new(&context);
	z_string_set_cstring(key3, "c", Z_STRING_ENCODING_UTF8);
	z_map_assign(mymap, key3, INT_TO_PTR(30));

	key4 = z_string_new(&context);
	z_string_set_cstring(key4, "d", Z_STRING_ENCODING_UTF8);
	z_map_assign(mymap, key4, INT_TO_PTR(40));

	key5 = z_string_new(&context);
	z_string_set_cstring(key5, "e", Z_STRING_ENCODING_UTF8);
	z_map_assign(mymap, key5, INT_TO_PTR(50));

	key6 = z_string_new(&context);
	z_string_set_cstring(key6, "f", Z_STRING_ENCODING_UTF8);
	z_map_assign(mymap, key6, INT_TO_PTR(60));

	it = z_map_find(mymap, key2);
	assert(it != NULL);
	z_map_erase1(mymap, it);
	z_object_unref(Z_OBJECT(it));

	it = z_map_find(mymap, key3);
	assert(it != NULL);
	z_map_erase1(mymap, it);
	z_object_unref(Z_OBJECT(it));

	it = z_map_find(mymap, key5);
	assert(it != NULL);
	z_map_erase(mymap, it, NULL);
	z_object_unref(Z_OBJECT(it));

	it = z_map_get_begin(mymap);
	end = z_map_get_end(mymap);

	printf("mymap contains:");

	for (i = 0; !z_map_iter_is_equal(it, end); z_map_iter_increment(it), ++i) {
		int x = PTR_TO_INT(z_map_get_value(mymap, it));
		printf(" %d", x);
		assert(test_result[i] == x);
	}

	printf("\n\n");
	z_object_unref(Z_OBJECT(end));
	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(mymap));
}

static void case7(void)
{
	/* Testing z_map_clear */
	ZMap *mymap;
	ZMapIter *it, *end;
	ZString *key;
	int test_result1[3] = { 100, 200, 300 };
	int test_result2[2] = { 1101, 2202 };
	int i;

	printf("======================\n");
	printf("ZMap case #7:\n");

	mymap = z_map_new(&context);
	z_map_set_key_destruct(mymap, (ZMapItemCallback) z_object_unref);
	z_map_set_compare(mymap, map_compare);

	key = z_string_new(&context);
	z_string_set_cstring(key, "x", Z_STRING_ENCODING_UTF8);
	z_map_assign(mymap, key, INT_TO_PTR(100));

	key = z_string_new(&context);
	z_string_set_cstring(key, "y", Z_STRING_ENCODING_UTF8);
	z_map_assign(mymap, key, INT_TO_PTR(200));

	key = z_string_new(&context);
	z_string_set_cstring(key, "z", Z_STRING_ENCODING_UTF8);
	z_map_assign(mymap, key, INT_TO_PTR(300));

	it = z_map_get_begin(mymap);
	end = z_map_get_end(mymap);

	printf("mymap contains:");

	for (i = 0; !z_map_iter_is_equal(it, end); z_map_iter_increment(it), ++i) {
		int x = PTR_TO_INT(z_map_get_value(mymap, it));
		printf(" %d", x);
		assert(test_result1[i] == x);
	}

	z_object_unref(Z_OBJECT(end));
	z_object_unref(Z_OBJECT(it));
	printf("\n\n");

	z_map_clear(mymap);

	key = z_string_new(&context);
	z_string_set_cstring(key, "a", Z_STRING_ENCODING_UTF8);
	z_map_assign(mymap, key, INT_TO_PTR(1101));

	key = z_string_new(&context);
	z_string_set_cstring(key, "b", Z_STRING_ENCODING_UTF8);
	z_map_assign(mymap, key, INT_TO_PTR(2202));

	it = z_map_get_begin(mymap);
	end = z_map_get_end(mymap);

	printf("mymap contains:");

	for (i = 0; !z_map_iter_is_equal(it, end); z_map_iter_increment(it), ++i) {
		int x = PTR_TO_INT(z_map_get_value(mymap, it));
		printf(" %d", x);
		assert(test_result2[i] == x);
	}

	printf("\n\n");

	z_object_unref(Z_OBJECT(end));
	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(mymap));
}

static void case8(void)
{
	/* Testing z_map_lower_bound / z_map_upper_bound */
	ZMap *mymap;
	ZMapIter *it, *end;
	ZString *key1, *key2, *key3, *key4, *key5;
	int test_result[2] = { 20, 100 };
	int i;

	printf("======================\n");
	printf("ZMap case #8:\n");

	mymap = z_map_new(&context);
	z_map_set_key_destruct(mymap, (ZMapItemCallback) z_object_unref);

	z_map_set_compare(mymap, map_compare);

	key1 = z_string_new(&context);
	z_string_set_cstring(key1, "a", Z_STRING_ENCODING_UTF8);
	z_map_assign(mymap, key1, INT_TO_PTR(20));

	key2 = z_string_new(&context);
	z_string_set_cstring(key2, "b", Z_STRING_ENCODING_UTF8);
	z_map_assign(mymap, key2, INT_TO_PTR(40));

	key3 = z_string_new(&context);
	z_string_set_cstring(key3, "c", Z_STRING_ENCODING_UTF8);
	z_map_assign(mymap, key3, INT_TO_PTR(60));

	key4 = z_string_new(&context);
	z_string_set_cstring(key4, "d", Z_STRING_ENCODING_UTF8);
	z_map_assign(mymap, key4, INT_TO_PTR(80));

	key5 = z_string_new(&context);
	z_string_set_cstring(key5, "e", Z_STRING_ENCODING_UTF8);
	z_map_assign(mymap, key5, INT_TO_PTR(100));

	it = z_map_lower_bound(mymap, key2);
	end = z_map_upper_bound(mymap, key4);

	z_map_erase(mymap, it, end);

	z_object_unref(Z_OBJECT(end));
	z_object_unref(Z_OBJECT(it));

	it = z_map_get_begin(mymap);
	end = z_map_get_end(mymap);

	printf("mymap contains:");

	for (i = 0; !z_map_iter_is_equal(it, end); z_map_iter_increment(it), ++i) {
		int x = PTR_TO_INT(z_map_get_value(mymap, it));
		printf(" %d", x);
		assert(test_result[i] == x);
	}

	printf("\n\n");
	z_object_unref(Z_OBJECT(mymap));
	z_object_unref(Z_OBJECT(end));
	z_object_unref(Z_OBJECT(it));
}


void z_map_test(int id)
{
	zco_context_init(&context);

	DEFINE_TEST(1, case1);
	DEFINE_TEST(2, case2);
	DEFINE_TEST(3, case3);
	DEFINE_TEST(4, case4);
	DEFINE_TEST(5, case5);
	DEFINE_TEST(6, case6);
	DEFINE_TEST(7, case7);
	DEFINE_TEST(8, case8);
}


