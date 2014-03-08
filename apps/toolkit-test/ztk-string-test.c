/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * ztk-string-test.c: ZtkString test driver
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


#include <zco-toolkit-test.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <z-string.h>
#include <z-string-iter.h>

#include <ztk-int32.h>
#include <ztk-string.h>
#include <ztk-console.h>
#include <ztk-string-iter.h>

static void case1(ZRuntimeContext *runtime_context)
{
        /* Test #1: string length */

        ZtkString *str = ztk_string_new(runtime_context);
        ztk_string_set_cstring(str, "Test string");

        ZtkInt32 *length = ztk_string_get_length(str);
        ZtkString *print_out = ztk_int32_to_string(length);

        ZtkConsole *console = ztk_console_new(runtime_context);
        ztk_console_write_text(console, print_out);

        z_object_unref(Z_OBJECT(console));
        z_object_unref(Z_OBJECT(print_out));
        z_object_unref(Z_OBJECT(length));
        z_object_unref(Z_OBJECT(str));
}

static void case2(ZRuntimeContext *runtime_context)
{
        /* Test #2: get character */

        ZtkString *str = ztk_string_new(runtime_context);
        ztk_string_set_cstring(str, "Test string");

        ZtkInt32 *advance_amount = ztk_int32_new(runtime_context);
        ztk_int32_set_value(advance_amount, 5);

        ZtkStringIter *it = ztk_string_get_begin(str);
        ztk_string_iter_advance(it, advance_amount);

        ZtkInt32 *unicode = ztk_string_get_char(str, it);
        ZtkString *print_out = ztk_int32_to_string(unicode);

        ZtkConsole *console = ztk_console_new(runtime_context);
        ztk_console_write_text(console, print_out);

        z_object_unref(Z_OBJECT(console));
        z_object_unref(Z_OBJECT(print_out));
        z_object_unref(Z_OBJECT(unicode));
        z_object_unref(Z_OBJECT(it));
        z_object_unref(Z_OBJECT(advance_amount));
        z_object_unref(Z_OBJECT(str));
}

static void case3(ZRuntimeContext *runtime_context)
{
        /* Test #3: append strings */

        ZtkString *str1 = ztk_string_new(runtime_context);
        ztk_string_set_cstring(str1, "Hello ");

        ZtkString *str2 = ztk_string_new(runtime_context);
        ztk_string_set_cstring(str2, "World");

        ZtkConsole *console = ztk_console_new(runtime_context);
        ztk_console_write_text(console, str1);
        ztk_console_write_text(console, str2);

        ztk_string_append(str1, str2);

        ztk_console_write_text(console, str1);
        ztk_console_write_text(console, str2);

        z_object_unref(Z_OBJECT(console));
        z_object_unref(Z_OBJECT(str2));
        z_object_unref(Z_OBJECT(str1));
}

static void case4(ZRuntimeContext *runtime_context)
{
        /* Test #4: set character */

        ZtkString *str = ztk_string_new(runtime_context);
        ztk_string_set_cstring(str, "A.C");

        ZtkStringIter *it = ztk_string_get_begin(str);
        ztk_string_iter_increment(it);

        ZtkInt32 *unicode = ztk_int32_new(runtime_context);
        ztk_int32_set_value(unicode, 66);

        ztk_string_set_char(str, it, unicode);

        ZtkConsole *console = ztk_console_new(runtime_context);
        ztk_console_write_text(console, str);

        z_object_unref(Z_OBJECT(console));
        z_object_unref(Z_OBJECT(unicode));
        z_object_unref(Z_OBJECT(it));
        z_object_unref(Z_OBJECT(str));
}

static void case5(ZRuntimeContext *runtime_context)
{
        /* Test #5: find() */

        ZtkString *hay = ztk_string_new(runtime_context);
        ztk_string_set_cstring(hay, "There are two needles in this haystack with needles");

        ZtkStringIter *iter = ztk_string_get_begin(hay);

        ZtkString *needle = ztk_string_new(runtime_context);
        ztk_string_set_cstring(needle, "needles");

        ZtkInt32 *flags = ztk_int32_new(runtime_context);
        ztk_int32_set_value(flags, 0);

        ZtkConsole *console = ztk_console_new(runtime_context);
        ztk_console_write_text(console, hay);
        ztk_console_write_text(console, needle);

        ZtkInt32 *ret = ztk_string_find(hay, iter, needle, flags);
        ZtkString *printout1 = ztk_int32_to_string(ret);

        ZtkInt32 *ret2 = ztk_string_iter_get_index(iter);
        ZtkString *printout2 = ztk_int32_to_string(ret2);

        ztk_console_write_text(console, printout1);
        ztk_console_write_text(console, printout2);

        z_object_unref(Z_OBJECT(printout2));
        z_object_unref(Z_OBJECT(printout1));
        z_object_unref(Z_OBJECT(ret2));
        z_object_unref(Z_OBJECT(ret));
        z_object_unref(Z_OBJECT(console));
        z_object_unref(Z_OBJECT(flags));
        z_object_unref(Z_OBJECT(needle));
        z_object_unref(Z_OBJECT(iter));
        z_object_unref(Z_OBJECT(hay));
}

static void case6(ZRuntimeContext *runtime_context)
{
        /* Test #6: rfind() */

        ZtkString *hay = ztk_string_new(runtime_context);
        ztk_string_set_cstring(hay, "There are two needles in this haystack with needles");

        ZtkStringIter *iter = ztk_string_get_end(hay);

        ZtkString *needle = ztk_string_new(runtime_context);
        ztk_string_set_cstring(needle, "needles");

        ZtkInt32 *flags = ztk_int32_new(runtime_context);
        ztk_int32_set_value(flags, 0);

        ZtkConsole *console = ztk_console_new(runtime_context);
        ztk_console_write_text(console, hay);
        ztk_console_write_text(console, needle);

        ZtkInt32 *ret = ztk_string_rfind(hay, iter, needle, flags);
        ZtkString *printout1 = ztk_int32_to_string(ret);

        ZtkInt32 *ret2 = ztk_string_iter_get_index(iter);
        ZtkString *printout2 = ztk_int32_to_string(ret2);

        ztk_console_write_text(console, printout1);
        ztk_console_write_text(console, printout2);

        z_object_unref(Z_OBJECT(printout2));
        z_object_unref(Z_OBJECT(printout1));
        z_object_unref(Z_OBJECT(ret2));
        z_object_unref(Z_OBJECT(ret));
        z_object_unref(Z_OBJECT(console));
        z_object_unref(Z_OBJECT(flags));
        z_object_unref(Z_OBJECT(needle));
        z_object_unref(Z_OBJECT(iter));
        z_object_unref(Z_OBJECT(hay));
}


static void case7(ZRuntimeContext *runtime_context)
{
        /* Test #7: compare() */

        ZtkString *str1 = ztk_string_new(runtime_context);
        ztk_string_set_cstring(str1, "Hello");

        ZtkString *str2 = ztk_string_new(runtime_context);
        ztk_string_set_cstring(str2, "World");

        ZtkConsole *console = ztk_console_new(runtime_context);
        ztk_console_write_text(console, str1);
        ztk_console_write_text(console, str2);

        ZtkStringIter *it1 = ztk_string_get_begin(str1);
        ZtkStringIter *it2 = ztk_string_get_begin(str2);
        ZtkInt32 *flags = ztk_int32_new(runtime_context);
        ztk_int32_set_value(flags, 0);

        ZtkInt32 *count = ztk_int32_new(runtime_context);
        ztk_int32_set_value(count, -1);

        ZtkInt32 *ret = ztk_string_compare(str1, it1, str2, it2, flags, count);
        ZtkString *printout = ztk_int32_to_string(ret);

        ztk_console_write_text(console, str1);
        ztk_console_write_text(console, str2);
        ztk_console_write_text(console, printout);

        z_object_unref(Z_OBJECT(printout));
        z_object_unref(Z_OBJECT(ret));
        z_object_unref(Z_OBJECT(count));
        z_object_unref(Z_OBJECT(flags));
        z_object_unref(Z_OBJECT(it2));
        z_object_unref(Z_OBJECT(it1));
        z_object_unref(Z_OBJECT(console));
        z_object_unref(Z_OBJECT(str2));
        z_object_unref(Z_OBJECT(str1));
}

static void case8(ZRuntimeContext *runtime_context)
{
        /* Test #8: insert() */

        ZtkInt32 *advance_amount = ztk_int32_new(runtime_context);

        ZtkString *hay = ztk_string_new(runtime_context);
        ztk_string_set_cstring(hay, "Hello World");

        ZtkStringIter *iter = ztk_string_get_begin(hay);
        ztk_int32_set_value(advance_amount, 6);
        ztk_string_iter_advance(iter, advance_amount);

        ZtkString *needle = ztk_string_new(runtime_context);
        ztk_string_set_cstring(needle, "everyone and the Under ");

        ZtkStringIter *first = ztk_string_get_begin(needle);

        ZtkStringIter *last = ztk_string_get_end(needle);
        ztk_int32_set_value(advance_amount, -6);
        ztk_string_iter_advance(last, advance_amount);

        ZtkConsole *console = ztk_console_new(runtime_context);
        ztk_console_write_text(console, hay);
        ztk_console_write_text(console, needle);

        ztk_string_insert(hay, iter, needle, first, last);

        ztk_console_write_text(console, hay);
        ztk_console_write_text(console, needle);

        z_object_unref(Z_OBJECT(console));
        z_object_unref(Z_OBJECT(last));
        z_object_unref(Z_OBJECT(first));
        z_object_unref(Z_OBJECT(needle));
        z_object_unref(Z_OBJECT(iter));
        z_object_unref(Z_OBJECT(hay));
        z_object_unref(Z_OBJECT(advance_amount));
}

static void case9(ZRuntimeContext *runtime_context)
{
        /* Test #9: toLowerCase() */

        ZtkString *str = ztk_string_new(runtime_context);
        ztk_string_set_cstring(str, "Hello World");

        ZtkConsole *console = ztk_console_new(runtime_context);

        ztk_console_write_text(console, str);
        ztk_string_to_lower_case(str);
        ztk_console_write_text(console, str);

        z_object_unref(Z_OBJECT(console));
        z_object_unref(Z_OBJECT(str));
}

static void case10(ZRuntimeContext *runtime_context)
{
        /* Test #10: toUpperCase() */

        ZtkString *str = ztk_string_new(runtime_context);
        ztk_string_set_cstring(str, "Hello World");

        ZtkConsole *console = ztk_console_new(runtime_context);

        ztk_console_write_text(console, str);
        ztk_string_to_upper_case(str);
        ztk_console_write_text(console, str);

        z_object_unref(Z_OBJECT(console));
        z_object_unref(Z_OBJECT(str));

}

static void case11(ZRuntimeContext *runtime_context)
{
        /* Test #11: tokenizer */

        ZtkConsole *console = ztk_console_new(runtime_context);

        ZtkString *str = ztk_string_new(runtime_context);
        ztk_string_set_cstring(str, "Hello everyone in the world");

        ZtkString *sep = ztk_string_new(runtime_context);
        ztk_string_set_cstring(sep, " ");

        ZtkStringIter *first = ztk_string_iter_new(runtime_context);
        ZtkStringIter *last = ztk_string_iter_new(runtime_context);

        ztk_string_token_start(str);

        ZtkInt32 *cond = ztk_int32_new(runtime_context);
        ztk_int32_set_value(cond, 1);

        ztk_while(cond, nonzero) {
                ZtkInt32 *rc = ztk_string_token_next(str, sep, first, last);
                ztk_int32_assign(cond, rc);
                z_object_unref(Z_OBJECT(rc));

                ZtkString *token = ztk_string_new(runtime_context);
                ZtkStringIter *it = ztk_string_get_begin(token);
                ztk_string_insert(token, it, str, first, last);

                ztk_console_write_text(console, token);

                z_object_unref(Z_OBJECT(it));
                z_object_unref(Z_OBJECT(token));

        } ztk_end_while(cond);

        z_object_unref(Z_OBJECT(cond));
        z_object_unref(Z_OBJECT(last));
        z_object_unref(Z_OBJECT(first));
        z_object_unref(Z_OBJECT(sep));
        z_object_unref(Z_OBJECT(str));
        z_object_unref(Z_OBJECT(console));
}

static void case12(ZRuntimeContext *runtime_context)
{
        /* Test #12: trim() */

        ZtkString *str = ztk_string_new(runtime_context);
        ztk_string_set_cstring(str, " Hello world ");

        ZtkConsole *console = ztk_console_new(runtime_context);

        ztk_console_write_text(console, str);
        ztk_string_trim(str);
        ztk_console_write_text(console, str);

        z_object_unref(Z_OBJECT(console));
        z_object_unref(Z_OBJECT(str));
}

void ztk_string_test(struct zco_context_t *context, int id)
{
        /* JavaScript properties/methods for the String object

           length:
                ztk_string_get_length can be used to get the length of the
                string.

           charAt, substr, slice, substring:
                charAt is similar to substr except that it assumes a string
                length of 1. slice and substring are also similar except that
                slice does not swap the iterators when needed. All four methods
                are similar in that they return a part of the given string.

                ztk_string_insert can be used to copy a portion of a string and
                insert it into another string. The destination string can be
                blank, in which case it would perform a similar operation as
                the four methods above.

           charCodeAt:
                ztk_string_get_char can be used to get the unicode value of a
                specific charactor in a string.

           concat:
                ztk_string_append can append two strings together.

           fromCharCode:
                ztk_string_set_char can change a character within a string to
                the one specified by the given unicode value.

           indexOf:
                ztk_string_find can search for a needle string within a hay
                string.

           lastIndexOf:
                ztk_string_rfind can reverse search for a needle string within
                a hay string.

           localeCompare:
                ztk_string_compare compares two strings with respect to the
                current locale.

           match, replace, search: (PLANNED)
                These functions are not yet implemented. There are plans to
                implement them under a different class, one that is focused
                on handling regular expressions.

           split:
                ztk_string_token_start and ztk_string_token_next can be used
                to iterate one token at a time. The same functionality as
                split() can be achieved using these methods.

           trim:
                ztk_string_trim strips off the space characters from the two
                ends of the string.

           toLocaleLowerCase, toLocaleUpperCase, toLowerCase, toUpperCase:
                ztk_string_to_lower_case and ztk_string_to_upper_case convert
                the string to lower case or upper case letters respectively.
                Both methods perform the conversion with respect to the
                current locale.

           toString, valueOf:
                These methods are meaningless to the application.
         */

	DEFINE_TEST(1, case1, context, "String test #1: string length");
	DEFINE_TEST(2, case2, context, "String test #2: get character");
	DEFINE_TEST(3, case3, context, "String test #3: append cstring");
	DEFINE_TEST(4, case4, context, "String test #4: set character");
	DEFINE_TEST(5, case5, context, "String test #5: find");
	DEFINE_TEST(6, case6, context, "String test #6: reverse find");
	DEFINE_TEST(7, case7, context, "String test #7: compare");
	DEFINE_TEST(8, case8, context, "String test #8: insert");
	DEFINE_TEST(9, case9, context, "String test #9: lower case");
	DEFINE_TEST(10, case10, context, "String test #10: upper case");
	DEFINE_TEST(11, case11, context, "String test #11: tokenizer");
	DEFINE_TEST(12, case12, context, "String test #12: trim");

}


