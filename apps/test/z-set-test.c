/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * z-set-test.c: ZSet test driver
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
#include <z-set.h>
#include <z-set-iter.h>
#include <z-string.h>
#include <z-string-iter.h>

#define INT_TO_PTR(x) ((void *) ((unsigned long) (x)))
#define PTR_TO_INT(x) ((int64_t) ((long) (x)))

static int set_compare(ZSet *self, const void *a, const void *b)
{
	return z_string_compare((ZString *) a, NULL, (ZString *) b, NULL, 0, -1);
}

static void case1(struct zco_context_t *context)
{
	/* Testing z_set_get_begin / z_set_get_end */
	ZSet *myset;
	ZSetIter *it, *end;
	ZString *key;
	char *test_result[3] = { "a", "b", "c" };
	int i;

	trace("======================\n");
	trace("ZSet case #1:\n");

        /* Here is a sequence of steps:
           1. set object is destroyed
           2. at some later point, the vector inside the set is disposed
           3. the set_item_destruct method is called during step #2
           4. the set object is already destroyed in step #1 so 'self' is undefined
         */

	myset = z_set_new(context, NULL);

	z_set_set_key_destruct(myset, (ZSetItemCallback) z_object_unref);
	z_set_set_compare(myset, set_compare);

	key = z_string_new(context, NULL);
	z_string_set_cstring(key, "b", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key);

	key = z_string_new(context, NULL);
	z_string_set_cstring(key, "a", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key);

	key = z_string_new(context, NULL);
	z_string_set_cstring(key, "c", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key);

	it = z_set_get_begin(myset);
	end = z_set_get_end(myset);

	trace("myset contains:");

	for (i = 0; !z_set_iter_is_equal(it, end); z_set_iter_increment(it), ++i) {
		ZString *key = z_set_get_key(myset, it);
                char *key_cstr = z_string_get_cstring(key, Z_STRING_ENCODING_UTF8);
		trace(" %s", key_cstr);
		assert(strcmp(test_result[i], key_cstr) == 0);
                free(key_cstr);
	}

	trace("\n\n");
	z_object_unref(Z_OBJECT(end));
	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(myset));
}

static void case2(struct zco_context_t *context)
{
	/* Testing z_set_is_empty */
	ZSet *myset;
	ZString *key;
	ZString *test_key[3];
	int i;

	trace("======================\n");
	trace("ZSet case #2:\n");

	myset = z_set_new(context, NULL);
	z_set_set_key_destruct(myset, (ZSetItemCallback) z_object_unref);
	z_set_set_compare(myset, set_compare);

	key = z_string_new(context, NULL);
	z_string_set_cstring(key, "a", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key);

	key = z_string_new(context, NULL);
	z_string_set_cstring(key, "b", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key);

	key = z_string_new(context, NULL);
	z_string_set_cstring(key, "c", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key);

	trace("myset contains:\n");

	/* create the test key strings */
	test_key[0] = z_string_new(context, NULL);
	test_key[1] = z_string_new(context, NULL);
	test_key[2] = z_string_new(context, NULL);

	z_string_set_cstring(test_key[0], "a", Z_STRING_ENCODING_UTF8);
	z_string_set_cstring(test_key[1], "b", Z_STRING_ENCODING_UTF8);
	z_string_set_cstring(test_key[2], "c", Z_STRING_ENCODING_UTF8);

	i = 0;

	while (!z_set_get_is_empty(myset)) {
		ZSetIter *first, *second;
		ZString *key;
		char *raw_key;
		int value;

		first = z_set_get_begin(myset);
		second = z_set_iter_dup(first);
		z_set_iter_increment(second);

		key = (ZString *) z_set_get_key(myset, first);
		raw_key = z_string_get_cstring(key, Z_STRING_ENCODING_UTF8);

		trace("\tkey: %s\n", raw_key);
		free(raw_key);

		assert(z_string_compare(key, NULL, test_key[i], NULL, 0, -1) == 0);

		z_set_erase(myset, first, second);
		z_object_unref(Z_OBJECT(second));
		z_object_unref(Z_OBJECT(first));
		++i;
	}

	z_object_unref(Z_OBJECT(test_key[2]));
	z_object_unref(Z_OBJECT(test_key[1]));
	z_object_unref(Z_OBJECT(test_key[0]));

	trace("\n\n");
	z_object_unref(Z_OBJECT(myset));
}

static void case3(struct zco_context_t *context)
{
	/* Testing z_set_get_size */
	ZSet *myset;
	ZString *key;
	int size;

	trace("======================\n");
	trace("ZSet case #3:\n");

	myset = z_set_new(context, NULL);
	z_set_set_key_destruct(myset, (ZSetItemCallback) z_object_unref);

	z_set_set_compare(myset, set_compare);

	key = z_string_new(context, NULL);
	z_string_set_cstring(key, "a", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key);

	key = z_string_new(context, NULL);
	z_string_set_cstring(key, "b", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key);

	key = z_string_new(context, NULL);
	z_string_set_cstring(key, "c", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key);

	size = z_set_get_size(myset);
	trace("myset size = %d\n", size);
	assert(size == 3);

	z_object_unref(Z_OBJECT(myset));
}

static void case4(struct zco_context_t *context)
{
	/* Testing z_set_find / z_set_assign */
	ZSet *myset;
	ZString *key1, *key2, *key3, *key4, *key;
	ZString *test_key1, *test_key2, *test_key3;
	ZSetIter *it;
	char *raw_str;
	int size, found;

	trace("======================\n");
	trace("ZSet case #4:\n");

	myset = z_set_new(context, NULL);
	z_set_set_key_destruct(myset, (ZSetItemCallback) z_object_unref);

	z_set_set_compare(myset, set_compare);

	/* first element */
	key1 = z_string_new(context, NULL);
	z_string_set_cstring(key1, "a", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key1);

	/* second element */
	key2 = z_string_new(context, NULL);
	z_string_set_cstring(key2, "b", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key2);

	/* third element */
	key3 = z_string_new(context, NULL);
	z_string_set_cstring(key3, "c", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key3);

	key4 = z_string_new(context, NULL);
	z_string_set_cstring(key4, "d", Z_STRING_ENCODING_UTF8);

	/* create test strings */
	test_key1 = z_string_new(context, NULL);
	z_string_set_cstring(test_key1, "a", Z_STRING_ENCODING_UTF8);

	test_key2 = z_string_new(context, NULL);
	z_string_set_cstring(test_key2, "b", Z_STRING_ENCODING_UTF8);

	test_key3 = z_string_new(context, NULL);
	z_string_set_cstring(test_key3, "c", Z_STRING_ENCODING_UTF8);

	/* print myset['a'] */
	it = z_set_find(myset, key1);
	assert(it != NULL);
	key = z_set_get_key(myset, it);
	z_object_unref(Z_OBJECT(it));
	assert(z_string_compare(key, NULL, test_key1, NULL, 0, -1) == 0);

	if (key) {
		raw_str = z_string_get_cstring(key, Z_STRING_ENCODING_UTF8);
		trace("myset['a'].key = %s\n", raw_str);
		free(raw_str);
	} else {
		trace("myset['a'].key = undefined\n");
	}

	/* print myset['b'] */
	it = z_set_find(myset, key2);
	assert(it != NULL);
	key = z_set_get_key(myset, it);
	z_object_unref(Z_OBJECT(it));
	assert(z_string_compare(key, NULL, test_key2, NULL, 0, -1) == 0);

	if (key) {
		raw_str = z_string_get_cstring(key, Z_STRING_ENCODING_UTF8);
		trace("myset['b'].key = %s\n", raw_str);
		free(raw_str);
	} else {
		trace("myset['b'].key = undefined\n");
	}

	/* print myset['c'] */
	it = z_set_find(myset, key3);
	assert(it != NULL);
	key = z_set_get_key(myset, it);
	z_object_unref(Z_OBJECT(it));
	assert(z_string_compare(key, NULL, test_key3, NULL, 0, -1) == 0);

	if (key) {
		raw_str = z_string_get_cstring(key, Z_STRING_ENCODING_UTF8);
		trace("myset['c'].key = %s\n", raw_str);
		free(raw_str);
	} else {
		trace("myset['c'].key = undefined\n");
	}

	/* print myset['d'] */
	it = z_set_find(myset, key4);
	assert(it == NULL);
	trace("myset['d'].key = (none)\n");

	size = z_set_get_size(myset);
	trace("myset size = %d\n", size);
	assert(size == 3);

	z_object_unref(Z_OBJECT(myset));
	z_object_unref(Z_OBJECT(test_key1));
	z_object_unref(Z_OBJECT(test_key2));
	z_object_unref(Z_OBJECT(test_key3));
	z_object_unref(Z_OBJECT(key4));
}

static void case5(struct zco_context_t *context)
{
	/* Testing z_set_insert */
	ZSet *myset;
	ZSetIter *it, *end;
	ZString *key;
	char *test_result[4] = { "a", "b", "c", "z" };
	int i;

	trace("======================\n");
	trace("ZSet case #5:\n");

	myset = z_set_new(context, NULL);
	z_set_set_key_destruct(myset, (ZSetItemCallback) z_object_unref);
	z_set_set_compare(myset, set_compare);

	key = z_string_new(context, NULL);
	z_string_set_cstring(key, "a", Z_STRING_ENCODING_UTF8);
	assert(z_set_insert(myset, key) == 0);

	key = z_string_new(context, NULL);
	z_string_set_cstring(key, "z", Z_STRING_ENCODING_UTF8);
	assert(z_set_insert(myset, key) == 0);

	key = z_string_new(context, NULL);
	z_string_set_cstring(key, "z", Z_STRING_ENCODING_UTF8);
	assert(z_set_insert(myset, key) == -1);
	z_object_unref(Z_OBJECT(key));

	key = z_string_new(context, NULL);
	z_string_set_cstring(key, "b", Z_STRING_ENCODING_UTF8);
	assert(z_set_insert(myset, key) == 0);

	key = z_string_new(context, NULL);
	z_string_set_cstring(key, "c", Z_STRING_ENCODING_UTF8);
	assert(z_set_insert(myset, key) == 0);

	it = z_set_get_begin(myset);
	end = z_set_get_end(myset);

	trace("myset contains:");

	for (i = 0; !z_set_iter_is_equal(it, end); z_set_iter_increment(it), ++i) {
		ZString *x = z_set_get_key(myset, it);
                char *key_cstr = z_string_get_cstring(x, Z_STRING_ENCODING_UTF8);
		trace(" %s", key_cstr);
		assert(strcmp(test_result[i], key_cstr) == 0);
                free(key_cstr);
	}

	trace("\n\n");
	z_object_unref(Z_OBJECT(myset));
	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(end));
}

static void case6(struct zco_context_t *context)
{
	/* Testing z_set_erase */
	ZSet *myset;
	ZSetIter *it, *end;
	ZString *key1, *key2, *key3, *key4, *key5, *key6;
	char *test_result[2] = { "a", "d" };
	int i;

	trace("======================\n");
	trace("ZSet case #6:\n");

	myset = z_set_new(context, NULL);
	z_set_set_key_destruct(myset, (ZSetItemCallback) z_object_unref);

	z_set_set_compare(myset, set_compare);

	key1 = z_string_new(context, NULL);
	z_string_set_cstring(key1, "a", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key1);

	key2 = z_string_new(context, NULL);
	z_string_set_cstring(key2, "b", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key2);

	key3 = z_string_new(context, NULL);
	z_string_set_cstring(key3, "c", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key3);

	key4 = z_string_new(context, NULL);
	z_string_set_cstring(key4, "d", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key4);

	key5 = z_string_new(context, NULL);
	z_string_set_cstring(key5, "e", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key5);

	key6 = z_string_new(context, NULL);
	z_string_set_cstring(key6, "f", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key6);

	it = z_set_find(myset, key2);
	assert(it != NULL);
	z_set_erase1(myset, it);
	z_object_unref(Z_OBJECT(it));

	it = z_set_find(myset, key3);
	assert(it != NULL);
	z_set_erase1(myset, it);
	z_object_unref(Z_OBJECT(it));

	it = z_set_find(myset, key5);
	assert(it != NULL);
	z_set_erase(myset, it, NULL);
	z_object_unref(Z_OBJECT(it));

	it = z_set_get_begin(myset);
	end = z_set_get_end(myset);

	trace("myset contains:");

	for (i = 0; !z_set_iter_is_equal(it, end); z_set_iter_increment(it), ++i) {
		ZString *x = z_set_get_key(myset, it);
                char *key_cstr = z_string_get_cstring(x, Z_STRING_ENCODING_UTF8);
		trace(" %s", key_cstr);
		assert(strcmp(test_result[i], key_cstr) == 0);
                free(key_cstr);
	}

	trace("\n\n");
	z_object_unref(Z_OBJECT(end));
	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(myset));
}

static void case7(struct zco_context_t *context)
{
	/* Testing z_set_clear */
	ZSet *myset;
	ZSetIter *it, *end;
	ZString *key;
	char *test_result1[3] = { "x", "y", "z" };
	char *test_result2[2] = { "a", "b" };
	int i;

	trace("======================\n");
	trace("ZSet case #7:\n");

	myset = z_set_new(context, NULL);
	z_set_set_key_destruct(myset, (ZSetItemCallback) z_object_unref);
	z_set_set_compare(myset, set_compare);

	key = z_string_new(context, NULL);
	z_string_set_cstring(key, "x", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key);

	key = z_string_new(context, NULL);
	z_string_set_cstring(key, "y", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key);

	key = z_string_new(context, NULL);
	z_string_set_cstring(key, "z", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key);

	it = z_set_get_begin(myset);
	end = z_set_get_end(myset);

	trace("myset contains:");

	for (i = 0; !z_set_iter_is_equal(it, end); z_set_iter_increment(it), ++i) {
		ZString *x = z_set_get_key(myset, it);
                char *key_cstr = z_string_get_cstring(x, Z_STRING_ENCODING_UTF8);
		trace(" %s", key_cstr);
		assert(strcmp(test_result1[i], key_cstr) == 0);
                free(key_cstr);
	}

	z_object_unref(Z_OBJECT(end));
	z_object_unref(Z_OBJECT(it));
	trace("\n\n");

	z_set_clear(myset);

	key = z_string_new(context, NULL);
	z_string_set_cstring(key, "a", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key);

	key = z_string_new(context, NULL);
	z_string_set_cstring(key, "b", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key);

	it = z_set_get_begin(myset);
	end = z_set_get_end(myset);

	trace("myset contains:");

	for (i = 0; !z_set_iter_is_equal(it, end); z_set_iter_increment(it), ++i) {
		ZString *x = z_set_get_key(myset, it);
                char *key_cstr = z_string_get_cstring(x, Z_STRING_ENCODING_UTF8);
		trace(" %s", key_cstr);
		assert(strcmp(test_result2[i], key_cstr) == 0);
                free(key_cstr);
	}

	trace("\n\n");

	z_object_unref(Z_OBJECT(end));
	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(myset));
}

static void case8(struct zco_context_t *context)
{
	/* Testing z_set_lower_bound / z_set_upper_bound */
	ZSet *myset;
	ZSetIter *it, *end;
	ZString *key1, *key2, *key3, *key4, *key5;
	char *test_result[2] = { "a", "e" };
	int i;

	trace("======================\n");
	trace("ZSet case #8:\n");

	myset = z_set_new(context, NULL);
	z_set_set_key_destruct(myset, (ZSetItemCallback) z_object_unref);

	z_set_set_compare(myset, set_compare);

	key1 = z_string_new(context, NULL);
	z_string_set_cstring(key1, "a", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key1);

	key2 = z_string_new(context, NULL);
	z_string_set_cstring(key2, "b", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key2);

	key3 = z_string_new(context, NULL);
	z_string_set_cstring(key3, "c", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key3);

	key4 = z_string_new(context, NULL);
	z_string_set_cstring(key4, "d", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key4);

	key5 = z_string_new(context, NULL);
	z_string_set_cstring(key5, "e", Z_STRING_ENCODING_UTF8);
	z_set_assign(myset, key5);

	it = z_set_lower_bound(myset, key2);
	end = z_set_upper_bound(myset, key4);

	z_set_erase(myset, it, end);

	z_object_unref(Z_OBJECT(end));
	z_object_unref(Z_OBJECT(it));

	it = z_set_get_begin(myset);
	end = z_set_get_end(myset);

	trace("myset contains:");

	for (i = 0; !z_set_iter_is_equal(it, end); z_set_iter_increment(it), ++i) {
		ZString *x = z_set_get_key(myset, it);
                char *key_cstr = z_string_get_cstring(x, Z_STRING_ENCODING_UTF8);
		trace(" %s", key_cstr);
		assert(strcmp(test_result[i], key_cstr) == 0);
                free(key_cstr);
	}

	trace("\n\n");
	z_object_unref(Z_OBJECT(myset));
	z_object_unref(Z_OBJECT(end));
	z_object_unref(Z_OBJECT(it));
}


void z_set_test(struct zco_context_t *context, int id)
{
	DEFINE_TEST(1, case1);
	DEFINE_TEST(2, case2);
	DEFINE_TEST(3, case3);
	DEFINE_TEST(4, case4);
	DEFINE_TEST(5, case5);
	DEFINE_TEST(6, case6);
	DEFINE_TEST(7, case7);
	DEFINE_TEST(8, case8);
}

