/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-string-test.c: String test driver
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
#include <z-string.h>
#include <z-string-iter.h>

static struct zco_context_t context;

static void print_string(ZString *str)
{
	char *out = z_string_get_cstring(str, Z_STRING_ENCODING_UTF8);
	printf("%s\n", out);
	free(out);
}

static void case1(void)
{
	/* Testing z_string_get_begin / z_string_get_end */

	char *test_string = "Test string";
	ZString *str;
	ZStringIter *it, *end;
	int i;

	printf("======================\n");
	printf("ZString case #1:\n");

	str = z_string_new(&context);
	z_string_set_cstring(str, test_string, Z_STRING_ENCODING_UTF8);

	it = z_string_get_begin(str);
	end = z_string_get_end(str);

	printf("string contains: ");

	for (i = 0; !z_string_iter_is_equal(it, end); z_string_iter_increment(it), ++i) {
		uint32_t ch = z_string_get_char(str, it);
		assert(test_string[i] == (int8_t) ch);
	}

	/* print the string */
	print_string(str);
	printf("\n");

	z_object_unref(Z_OBJECT(str));
	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(end));
}

static void case2(void)
{
	/* Testing z_string_get_length */

	char *test_string = "Test string";
	ZString *str;
	int size, length;

	printf("======================\n");
	printf("ZString case #2:\n");

	str = z_string_new(&context);
	z_string_set_cstring(str, test_string, Z_STRING_ENCODING_UTF8);
	length = z_string_get_length(str);

	printf("The length of the string is %d characters\n", length);
	printf("\n\n");

	assert(length == 11);

	z_object_unref(Z_OBJECT(str));
}

static void case3(void)
{
	/* Testing z_string_clear / z_string_get_is_empty */
	char *test_string = "Test string";
	ZStringIter *it, *end;
	ZString *str;
	int i, length;

	printf("======================\n");
	printf("ZString case #3:\n");

	str = z_string_new(&context);
	z_string_set_cstring(str, test_string, Z_STRING_ENCODING_UTF8);

	printf("string contains (before clearing): ");

	it = z_string_get_begin(str);
	end = z_string_get_end(str);

	for (i = 0; !z_string_iter_is_equal(it, end); z_string_iter_increment(it), ++i) {
		uint32_t ch = z_string_get_char(str, it);
		assert(test_string[i] == (int8_t) ch);
	}

	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(end));

	/* print the string */
	print_string(str);

	length = z_string_get_length(str);

	printf("The length of the string is %d characters\n", length);
	printf("String is empty: %d\n", z_string_get_is_empty(str));
	printf("\n\n");

	assert(length == 11);

	z_string_clear(str);

	printf("string contains (after clearing): ");

	it = z_string_get_begin(str);
	end = z_string_get_end(str);

	for (i = 0; !z_string_iter_is_equal(it, end); z_string_iter_increment(it), ++i) {
		uint32_t ch = z_string_get_char(str, it);
		assert(test_string[i] == (int8_t) ch);
	}

	/* print the string */
	print_string(str);

	length = z_string_get_length(str);

	printf("The length of the string is %d characters\n", length);
	printf("String is empty: %d\n", z_string_get_is_empty(str));
	printf("\n\n");

	assert(length == 0);

	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(end));
	z_object_unref(Z_OBJECT(str));
}

static void case4(void)
{
	/* Testing z_string_append  */
	char test_string1[] = "This is my first string. ";
	char test_string2[] = "This is my second string. ";
	char test_string12[] = "This is my first string. This is my second string. ";
	ZStringIter *it, *end;
	ZString *str1, *str2, *str3;
	int i, length;

	printf("======================\n");
	printf("ZString case #4:\n");

	str1 = z_string_new(&context);
	str2 = z_string_new(&context);
	str3 = z_string_new(&context);

	z_string_set_cstring(str2, test_string1, Z_STRING_ENCODING_UTF8);
	z_string_set_cstring(str3, test_string2, Z_STRING_ENCODING_UTF8);

	printf("string contains (before appending anything): ");

	it = z_string_get_begin(str1);
	end = z_string_get_end(str1);

	for (i = 0; !z_string_iter_is_equal(it, end); z_string_iter_increment(it), ++i) {
		/* string should be empty */
		assert(0);
		break;
	}

	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(end));

	/* print the string */
	print_string(str1);

	length = z_string_get_length(str1);

	printf("The length of the string is %d characters\n", length);
	printf("\n\n");

	assert(length == 0);

	z_string_append(str1, str2, NULL, NULL);
	z_object_unref(Z_OBJECT(str2));

	printf("string contains (after appending first string): ");

	it = z_string_get_begin(str1);
	end = z_string_get_end(str1);

	for (i = 0; !z_string_iter_is_equal(it, end); z_string_iter_increment(it), ++i) {
		uint32_t ch = z_string_get_char(str1, it);
		assert(test_string1[i] == (int8_t) ch);
	}

	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(end));

	/* print the string */
	print_string(str1);

	length = z_string_get_length(str1);

	printf("The length of the string is %d characters\n", length);
	printf("\n\n");

	assert(length == sizeof(test_string1) - 1);

	z_string_append(str1, str3, NULL, NULL);
	z_object_unref(Z_OBJECT(str3));

	printf("string contains (after appending both strings): ");

	it = z_string_get_begin(str1);
	end = z_string_get_end(str1);

	for (i = 0; !z_string_iter_is_equal(it, end); z_string_iter_increment(it), ++i) {
		uint32_t ch = z_string_get_char(str1, it);
		assert(test_string12[i] == (int8_t) ch);
	}

	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(end));

	/* print the string */
	print_string(str1);

	length = z_string_get_length(str1);

	printf("The length of the string is %d characters\n", length);
	printf("\n\n");

	assert(length == sizeof(test_string12) - 1);

	z_object_unref(Z_OBJECT(str1));
}

static void case5(void)
{
	/* Testing z_string_push_back */
	char test_string[] = "Test string";
	ZString *str;
	ZStringIter *it, *end;
	int i;

	printf("======================\n");
	printf("ZString case #5:\n");

	str = z_string_new(&context);

	for (i = 0; i < sizeof(test_string) - 1; ++i) {
		z_string_push_back(str, test_string[i]);
	}

	it = z_string_get_begin(str);
	end = z_string_get_end(str);

	printf("string contains: ");

	for (i = 0; !z_string_iter_is_equal(it, end); z_string_iter_increment(it), ++i) {
		uint32_t ch = z_string_get_char(str, it);
		assert(test_string[i] == (int8_t) ch);
	}

	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(end));

	/* print the string */
	print_string(str);
	printf("\n");

	z_object_unref(Z_OBJECT(str));
}

static void case6(void)
{
	/* Testing z_string_insert */
	char test_string1[] = "This is noise. This is my first string. This is also my first string. This is noise. ";
	char test_string2[] = "This is noise. This is my second string. This is noise. ";
	char test_string12[] = "This is my first string. This is my second string. This is also my first string. ";

	ZString *str1, *str2, *str3;
	ZStringIter *it, *first, *last, *end;
	int i;

	printf("======================\n");
	printf("ZString case #6:\n");

	str1 = z_string_new(&context);
	str2 = z_string_new(&context);
	str3 = z_string_new(&context);

	z_string_set_cstring(str1, test_string1, Z_STRING_ENCODING_UTF8);
	z_string_set_cstring(str2, test_string2, Z_STRING_ENCODING_UTF8);

	it = z_string_get_begin(str3);
	first = z_string_get_begin(str1);
	last = z_string_get_end(str1);
	z_string_iter_advance(first, 15);
	z_string_iter_advance(last, -15);
	z_string_insert(str3, it, str1, first, last);
	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(first));
	z_object_unref(Z_OBJECT(last));

	it = z_string_get_begin(str3);
	first = z_string_get_begin(str2);
	last = z_string_get_end(str2);
	z_string_iter_advance(it, 25);
	z_string_iter_advance(first, 15);
	z_string_iter_advance(last, -15);
	z_string_insert(str3, it, str2, first, last);
	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(first));
	z_object_unref(Z_OBJECT(last));

	it = z_string_get_begin(str3);
	end = z_string_get_end(str3);

	printf("string contains: ");

	for (i = 0; !z_string_iter_is_equal(it, end); z_string_iter_increment(it), ++i) {
		uint32_t ch = z_string_get_char(str3, it);
		assert(test_string12[i] == (int8_t) ch);
	}

	/* print the string */
	print_string(str3);
	printf("\n");

	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(end));

	z_object_unref(Z_OBJECT(str3));
	z_object_unref(Z_OBJECT(str2));
	z_object_unref(Z_OBJECT(str1));
}

static void case7(void)
{
	/* Testing z_string_insert_char */
	char test_string1[] = "This is my first string. This is also my first string. ";
	char test_string2[] = "This is my second string. ";
	char test_string12[] =
	    "This is my first string. TThhiiss  iiss  mmyy  sseeccoonndd  ssttrriinngg..  This is also my first string. ";

	ZString *str1, *str2, *str3;
	ZStringIter *it, *first, *last, *end;
	int i, len;

	printf("======================\n");
	printf("ZString case #7:\n");

	str1 = z_string_new(&context);
	str2 = z_string_new(&context);
	str3 = z_string_new(&context);

	z_string_set_cstring(str1, test_string1, Z_STRING_ENCODING_UTF8);
	z_string_set_cstring(str2, test_string2, Z_STRING_ENCODING_UTF8);

	it = z_string_get_begin(str3);
	first = z_string_get_begin(str1);
	last = z_string_get_end(str1);
	z_string_insert(str3, it, str1, first, last);

	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(first));
	z_object_unref(Z_OBJECT(last));

	it = z_string_get_begin(str3);
	z_string_iter_advance(it, 25);

	len = strlen(test_string2);

	for (i = 0; i < len; ++i) {
		z_string_insert_char(str3, it, 2, test_string2[i]);
		z_string_iter_advance(it, 2);
	}

	z_object_unref(Z_OBJECT(it));

	it = z_string_get_begin(str3);
	end = z_string_get_end(str3);

	printf("string contains: ");

	for (i = 0; !z_string_iter_is_equal(it, end); z_string_iter_increment(it), ++i) {
		uint32_t ch = z_string_get_char(str3, it);
		assert(test_string12[i] == (int8_t) ch);
	}

	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(end));

	/* print the string */
	print_string(str3);
	printf("\n");

	z_object_unref(Z_OBJECT(str3));
	z_object_unref(Z_OBJECT(str2));
	z_object_unref(Z_OBJECT(str1));
}

static void case8(void)
{
	/* Testing z_string_erase */
	char test_string1[] = "This is my first string. This will be deleted. This is also my first string. ";
	char test_string12[] = "This is my first string. This is also my first string. ";

	ZString *str1;
	ZStringIter *it, *end;
	int i;

	printf("======================\n");
	printf("ZString case #8:\n");

	str1 = z_string_new(&context);
	z_string_set_cstring(str1, test_string1, Z_STRING_ENCODING_UTF8);

	/* erase the middle sentence from the string */
	it = z_string_get_begin(str1);
	end = z_string_get_end(str1);
	z_string_iter_advance(it, 25);
	z_string_iter_advance(end, -30);
	z_string_erase(str1, it, end);

	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(end));

	/* print the new string */
	it = z_string_get_begin(str1);
	end = z_string_get_end(str1);

	printf("string contains: ");

	for (i = 0; !z_string_iter_is_equal(it, end); z_string_iter_increment(it), ++i) {
		uint32_t ch = z_string_get_char(str1, it);
		assert(test_string12[i] == (int8_t) ch);
	}

	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(end));

	/* print the string */
	print_string(str1);
	printf("\n");

	z_object_unref(Z_OBJECT(str1));
}

static void case9(void)
{
	/* Testing z_string_replace */
	char test_string1[] =
	    "This is noise. This is my first string. This will be deleted. This is also my first string. This is noise. ";
	char test_string2[] = "This is noise. This is my second string. This is noise. ";
	char test_string12[] = "This is my first string. This is my second string. This is also my first string. ";

	ZString *str1, *str2, *str3;
	ZStringIter *it1, *it2, *first, *last, *end;
	int i;

	printf("======================\n");
	printf("ZString case #9:\n");

	str1 = z_string_new(&context);
	str2 = z_string_new(&context);
	str3 = z_string_new(&context);

	z_string_set_cstring(str1, test_string1, Z_STRING_ENCODING_UTF8);
	z_string_set_cstring(str2, test_string2, Z_STRING_ENCODING_UTF8);

	it1 = z_string_get_begin(str3);
	first = z_string_get_begin(str1);
	last = z_string_get_end(str1);
	z_string_iter_advance(first, 15);
	z_string_iter_advance(last, -15);
	z_string_insert(str3, it1, str1, first, last);

	z_object_unref(Z_OBJECT(it1));
	z_object_unref(Z_OBJECT(first));
	z_object_unref(Z_OBJECT(last));

	it1 = z_string_get_begin(str3);
	first = z_string_get_begin(str2);
	last = z_string_get_end(str2);
	z_string_iter_advance(it1, 25);
	z_string_iter_advance(first, 15);
	z_string_iter_advance(last, -15);

	it2 = z_string_iter_dup(it1);
	z_string_iter_advance(it2, 22);
	z_string_replace(str3, it1, it2, str2, first, last);

	z_object_unref(Z_OBJECT(it1));
	z_object_unref(Z_OBJECT(it2));
	z_object_unref(Z_OBJECT(first));
	z_object_unref(Z_OBJECT(last));

	printf("string contains: ");

	it1 = z_string_get_begin(str3);
	end = z_string_get_end(str3);

	for (i = 0; !z_string_iter_is_equal(it1, end); z_string_iter_increment(it1), ++i) {
		uint32_t ch = z_string_get_char(str3, it1);
		assert(test_string12[i] == (int8_t) ch);
	}

	z_object_unref(Z_OBJECT(it1));
	z_object_unref(Z_OBJECT(end));

	/* print the string */
	print_string(str3);
	printf("\n");

	z_object_unref(Z_OBJECT(str3));
	z_object_unref(Z_OBJECT(str2));
	z_object_unref(Z_OBJECT(str1));
}

static void case10(void)
{
	/* Testing z_string_insert_char */
	char test_string1[] =
	    "This is my first string. XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXThis is also my first string. ";
	char test_string2[] = "This is my second string. ";
	char test_string12[] =
	    "This is my first string. TThhiiss  iiss  mmyy  sseeccoonndd  ssttrriinngg..  This is also my first string. ";

	ZString *str1, *str2, *str3;
	ZStringIter *it1, *it2, *first, *last, *end;
	int i, len;

	printf("======================\n");
	printf("ZString case #10:\n");

	str1 = z_string_new(&context);
	str2 = z_string_new(&context);
	str3 = z_string_new(&context);

	z_string_set_cstring(str1, test_string1, Z_STRING_ENCODING_UTF8);
	z_string_set_cstring(str2, test_string2, Z_STRING_ENCODING_UTF8);

	it1 = z_string_get_begin(str3);
	first = z_string_get_begin(str1);
	last = z_string_get_end(str1);
	z_string_insert(str3, it1, str1, first, last);

	z_object_unref(Z_OBJECT(it1));
	z_object_unref(Z_OBJECT(first));
	z_object_unref(Z_OBJECT(last));

	it1 = z_string_get_begin(str3);
	z_string_iter_advance(it1, 25);

	it2 = z_string_iter_dup(it1);
	z_string_iter_advance(it2, 2);

	len = strlen(test_string2);

	for (i = 0; i < len; ++i) {
		z_string_replace_with_chars(str3, it1, it2, 2, test_string2[i]);
		z_string_iter_advance(it1, 2);
		z_string_iter_advance(it2, 2);
	}

	z_object_unref(Z_OBJECT(it1));
	z_object_unref(Z_OBJECT(it2));

	it1 = z_string_get_begin(str3);
	end = z_string_get_end(str3);

	printf("string contains: ");

	for (i = 0; !z_string_iter_is_equal(it1, end); z_string_iter_increment(it1), ++i) {
		uint32_t ch = z_string_get_char(str3, it1);
		assert(test_string12[i] == (int8_t) ch);
	}

	z_object_unref(Z_OBJECT(it1));
	z_object_unref(Z_OBJECT(end));

	/* print the string */
	print_string(str3);
	printf("\n");

	z_object_unref(Z_OBJECT(str3));
	z_object_unref(Z_OBJECT(str2));
	z_object_unref(Z_OBJECT(str1));
}


static void case11(void)
{
	/* Testing z_string_get_cstring */
	ZString *str;
	char *buffer;
	char test_string[] = "This is my first string. ";
	int i, size;

	printf("======================\n");
	printf("ZString case #11:\n");

	str = z_string_new(&context);

	z_string_set_cstring(str, test_string, Z_STRING_ENCODING_UTF8);
	buffer = z_string_get_cstring(str, Z_STRING_ENCODING_UTF8);

	size = sizeof(test_string);

	for (i = 0; i < size; ++i) {
		fputc(buffer[i], stdout);
		assert(buffer[i] == test_string[i]);
	}

	free(buffer);
	z_object_unref(Z_OBJECT(str));

	printf("\n\n");
}

static void case12(void)
{
	/* Testing z_string_compare */
	char test_red[] = "red apple";
	char test_green[] = "green apple";
	char test_apple[] = "apple";
	ZString *red, *green, *apple;
	ZStringIter *it1, *it2;
	int rc;

	printf("======================\n");
	printf("ZString case #12:\n");

	red = z_string_new(&context);
	green = z_string_new(&context);
	apple = z_string_new(&context);

	z_string_set_cstring(red, test_red, Z_STRING_ENCODING_UTF8);
	z_string_set_cstring(green, test_green, Z_STRING_ENCODING_UTF8);
	z_string_set_cstring(apple, test_apple, Z_STRING_ENCODING_UTF8);

	it1 = z_string_get_begin(green);
	it2 = z_string_get_begin(red);
	rc = z_string_compare(green, it1, red, it2, 0, -1);
	assert(rc < 0);
	printf("comparing %s[0..10] with %s[0..8]: %d\n", test_green, test_red, rc);

	z_object_unref(Z_OBJECT(it1));
	z_object_unref(Z_OBJECT(it2));

	it1 = z_string_get_begin(green);
	it2 = z_string_get_begin(apple);
	z_string_iter_advance(it1, 6);
	rc = z_string_compare(green, it1, apple, it2, 0, 5);
	assert(rc == 0);
	printf("comparing %s[6..10] with %s[0..4]: %d\n", test_green, test_apple, rc);

	z_object_unref(Z_OBJECT(it1));
	z_object_unref(Z_OBJECT(it2));

	it1 = z_string_get_begin(red);
	it2 = z_string_get_begin(apple);
	z_string_iter_advance(it1, 4);
	rc = z_string_compare(red, it1, apple, it2, 0, 5);
	assert(rc == 0);
	printf("comparing %s[4..8] with %s[0..4]: %d\n", test_red, test_apple, rc);

	z_object_unref(Z_OBJECT(it1));
	z_object_unref(Z_OBJECT(it2));

	it1 = z_string_get_begin(green);
	it2 = z_string_get_begin(red);
	z_string_iter_advance(it1, 6);
	z_string_iter_advance(it2, 4);
	rc = z_string_compare(green, it1, red, it2, 0, 5);
	assert(rc == 0);
	printf("comparing %s[6..10] with %s[4..8]: %d\n", test_green, test_red, rc);

	z_object_unref(Z_OBJECT(it1));
	z_object_unref(Z_OBJECT(it2));
	z_object_unref(Z_OBJECT(apple));
	z_object_unref(Z_OBJECT(green));
	z_object_unref(Z_OBJECT(red));

	fputs("\n", stdout);
}

static void case13(void)
{
	/* Testing z_string_find_char */
	ZString *hay;
	ZStringIter *it;
	char test_hay[] = "This is first. This is second. This is third.";
	int idx, position, positions[3] = { 13, 29, 44 };

	printf("======================\n");
	printf("ZString case #13:\n");

	hay = z_string_new(&context);

	z_string_set_cstring(hay, test_hay, Z_STRING_ENCODING_UTF8);
	it = z_string_get_begin(hay);

	idx = 0;

	while (z_string_find_char(hay, it, '.', 0)) {
		position = z_string_iter_get_index(it);

		printf("needle found in position: %d\n", position);
		fflush(stdout);

		assert(position == positions[idx]);
		++idx;

		z_string_iter_increment(it);
	}

	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(hay));

	printf("\n\n");
}

static void case14(void)
{
	/* Testing z_string_find */

	ZString *hay, *needle;
	ZStringIter *it;
	char test_hay[] = "There are two needles in this haystack with needles.";
	char test_needle[] = "needle";
	int idx, position, positions[2] = { 14, 44 };

	printf("======================\n");
	printf("ZString case #14:\n");

	hay = z_string_new(&context);
	needle = z_string_new(&context);

	z_string_set_cstring(hay, test_hay, Z_STRING_ENCODING_UTF8);
	z_string_set_cstring(needle, test_needle, Z_STRING_ENCODING_UTF8);
	it = z_string_get_begin(hay);

	idx = 0;
	while (z_string_find(hay, it, needle, 0)) {
		position = z_string_iter_get_index(it);

		printf("needle found in position: %d\n", position);
		fflush(stdout);

		assert(position == positions[idx]);
		++idx;

		z_string_iter_increment(it);
	}

	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(needle));
	z_object_unref(Z_OBJECT(hay));

	printf("\n\n");
}

static void case15(void)
{
	/* Testing z_string_find_any_char (positive) */

	ZString *hay, *list;
	ZStringIter *it, *end;
	char test_hay[] = "Replace the vowels in this sentence by asterisks.";
	char test_string[] = "R*pl*c* th* v*w*ls *n th*s s*nt*nc* by *st*r*sks.";
	int idx;

	printf("======================\n");
	printf("ZString case #15:\n");

	hay = z_string_new(&context);
	list = z_string_new(&context);

	z_string_set_cstring(hay, test_hay, Z_STRING_ENCODING_UTF8);
	z_string_set_cstring(list, "aeiou", Z_STRING_ENCODING_UTF8);
	it = z_string_get_begin(hay);

	while (z_string_find_any_char(hay, it, list, 0)) {
		z_string_set_char(hay, it, (uint32_t) '*');
		z_string_iter_increment(it);
	}

	z_object_unref(Z_OBJECT(it));

	it = z_string_get_begin(hay);
	end = z_string_get_end(hay);

	for (idx = 0; !z_string_iter_is_equal(it, end); z_string_iter_increment(it), ++idx) {
		uint32_t ch = z_string_get_char(hay, it);
		assert(test_string[idx] == (int8_t) ch);
	}

	/* print the string */
	print_string(hay);
	printf("\n");

	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(end));
	z_object_unref(Z_OBJECT(list));
	z_object_unref(Z_OBJECT(hay));
}

static void case16(void)
{
	/* Testing z_string_find_any_char (negative) */

	ZString *hay, *list;
	ZStringIter *it, *end;
	char test_hay[] = "Replace the consonants in this sentence by asterisks.";
	char test_string[] = "*e**a*e **e *o**o*a*** i* **i* *e**e**e ** a**e*i***.";
	int idx;

	printf("======================\n");
	printf("ZString case #16:\n");

	hay = z_string_new(&context);
	list = z_string_new(&context);

	z_string_set_cstring(hay, test_hay, Z_STRING_ENCODING_UTF8);
	z_string_set_cstring(list, "aeiou. ", Z_STRING_ENCODING_UTF8);
	it = z_string_get_begin(hay);

	while (z_string_find_any_char(hay, it, list, Z_STRING_FLAG_NEGATIVE)) {
		z_string_set_char(hay, it, (uint32_t) '*');
		z_string_iter_increment(it);
	}

	z_object_unref(Z_OBJECT(it));

	it = z_string_get_begin(hay);
	end = z_string_get_end(hay);

	for (idx = 0; !z_string_iter_is_equal(it, end); z_string_iter_increment(it), ++idx) {
		uint32_t ch = z_string_get_char(hay, it);
		assert(test_string[idx] == (int8_t) ch);
	}

	/* print the string */
	print_string(hay);
	printf("\n");

	z_object_unref(Z_OBJECT(it));
	z_object_unref(Z_OBJECT(end));
	z_object_unref(Z_OBJECT(list));
	z_object_unref(Z_OBJECT(hay));
}

static void case17(void)
{
	/* Testing z_string_token_start / z_string_token_next */
	#define DOLLAR "\x24"
	#define CENT "\xc2\xa2"
	#define EURO "\xe2\x82\xac"

	ZString *hay;
	ZString *space_string;
	char test_hay[] = "dollar_" DOLLAR " cent_" CENT " euro_" EURO " one two three four five";
	char *tokens[] = { "dollar_" DOLLAR, "cent_" CENT, "euro_" EURO, "one", "two",
		"three", "four", "five"
	};
	int i;

	printf("======================\n");
	printf("ZString case #17:\n");

	hay = z_string_new(&context);
	space_string = z_string_new(&context);

	z_string_set_cstring(hay, test_hay, Z_STRING_ENCODING_UTF8);
	z_string_set_cstring(space_string, " ", Z_STRING_ENCODING_UTF8);

	print_string(hay);
	z_string_token_start(hay);

	i = 0;

	while (1) {
		ZString *test_token, *token;
		ZStringIter *first, *last;

		first = z_string_iter_new(&context);
		last = z_string_iter_new(&context);

		int rc = z_string_token_next(hay, space_string, first, last);

		test_token = z_string_new(&context);
		z_string_set_cstring(test_token, tokens[i], Z_STRING_ENCODING_UTF8);

		token = z_string_new(&context);
		z_string_append(token, hay, first, last);
		print_string(token);

		/* compare the fetched token with the test token */
		assert(z_string_compare(token, NULL, test_token, NULL, 0, z_string_get_length(test_token)) == 0);

		/* compare the substring of the hay (supposibly the token) with the test token */
		assert(z_string_compare(hay, first, test_token, NULL, 0, z_string_get_length(test_token)) == 0);

		z_object_unref(Z_OBJECT(token));
		z_object_unref(Z_OBJECT(test_token));
		z_object_unref(Z_OBJECT(last));
		z_object_unref(Z_OBJECT(first));

		if (rc == 0)
			break;

		++i;
	}

	z_object_unref(Z_OBJECT(space_string));
	z_object_unref(Z_OBJECT(hay));

	printf("\n\n");
}

void z_string_test(int id)
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
	DEFINE_TEST(9, case9);
	DEFINE_TEST(10, case10);
	DEFINE_TEST(11, case11);
	DEFINE_TEST(12, case12);
	DEFINE_TEST(13, case13);
	DEFINE_TEST(14, case14);
	DEFINE_TEST(15, case15);
	DEFINE_TEST(16, case16);
	DEFINE_TEST(17, case17);

	zco_context_destroy(&context);
}


