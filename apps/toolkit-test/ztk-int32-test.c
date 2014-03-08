/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * ztk-int32-test.c: ZtkInt32 test driver
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
        /* Test #1: add */

        ZtkInt32 *a = ztk_int32_new(runtime_context);
        ztk_int32_set_value(a, 1);

        ZtkInt32 *b = ztk_int32_new(runtime_context);
        ztk_int32_set_value(b, 2);

        ZtkString *temp1 = ztk_int32_to_string(a);
        ztk_int32_add(a, b);
        ZtkString *temp2 = ztk_int32_to_string(a);

        ZtkConsole *console = ztk_console_new(runtime_context);
        ztk_console_write_text(console, temp1);
        ztk_console_write_text(console, temp2);

        z_object_unref(Z_OBJECT(console));
        z_object_unref(Z_OBJECT(temp2));
        z_object_unref(Z_OBJECT(temp1));
        z_object_unref(Z_OBJECT(b));
        z_object_unref(Z_OBJECT(a));
}

static void case2(ZRuntimeContext *runtime_context)
{
        /* Test #2: subtract */

        ZtkInt32 *a = ztk_int32_new(runtime_context);
        ztk_int32_set_value(a, 3);

        ZtkInt32 *b = ztk_int32_new(runtime_context);
        ztk_int32_set_value(b, 1);

        ZtkString *temp1 = ztk_int32_to_string(a);
        ztk_int32_subtract(a, b);
        ZtkString *temp2 = ztk_int32_to_string(a);

        ZtkConsole *console = ztk_console_new(runtime_context);
        ztk_console_write_text(console, temp1);
        ztk_console_write_text(console, temp2);

        z_object_unref(Z_OBJECT(console));
        z_object_unref(Z_OBJECT(temp2));
        z_object_unref(Z_OBJECT(temp1));
        z_object_unref(Z_OBJECT(b));
        z_object_unref(Z_OBJECT(a));
}

static void case3(ZRuntimeContext *runtime_context)
{
        /* Test #3: multiply */

        ZtkInt32 *a = ztk_int32_new(runtime_context);
        ztk_int32_set_value(a, 3);

        ZtkInt32 *b = ztk_int32_new(runtime_context);
        ztk_int32_set_value(b, 2);

        ZtkString *temp1 = ztk_int32_to_string(a);
        ztk_int32_multiply(a, b);
        ZtkString *temp2 = ztk_int32_to_string(a);

        ZtkConsole *console = ztk_console_new(runtime_context);
        ztk_console_write_text(console, temp1);
        ztk_console_write_text(console, temp2);

        z_object_unref(Z_OBJECT(console));
        z_object_unref(Z_OBJECT(temp2));
        z_object_unref(Z_OBJECT(temp1));
        z_object_unref(Z_OBJECT(b));
        z_object_unref(Z_OBJECT(a));
}

static void case4(ZRuntimeContext *runtime_context)
{
        /* Test #4: divide */

        ZtkInt32 *a = ztk_int32_new(runtime_context);
        ztk_int32_set_value(a, 100);

        ZtkInt32 *b = ztk_int32_new(runtime_context);
        ztk_int32_set_value(b, 7);

        ZtkString *temp1 = ztk_int32_to_string(a);
        ztk_int32_divide(a, b);
        ZtkString *temp2 = ztk_int32_to_string(a);

        ZtkConsole *console = ztk_console_new(runtime_context);
        ztk_console_write_text(console, temp1);
        ztk_console_write_text(console, temp2);

        z_object_unref(Z_OBJECT(console));
        z_object_unref(Z_OBJECT(temp2));
        z_object_unref(Z_OBJECT(temp1));
        z_object_unref(Z_OBJECT(b));
        z_object_unref(Z_OBJECT(a));
}

static void case5(ZRuntimeContext *runtime_context)
{
        /* Test #5: or */

        ZtkInt32 *a = ztk_int32_new(runtime_context);
        ztk_int32_set_value(a, 1);

        ZtkInt32 *b = ztk_int32_new(runtime_context);
        ztk_int32_set_value(b, 0);

        ZtkString *temp1 = ztk_int32_to_string(a);
        ztk_int32_or_operator(a, b);
        ZtkString *temp2 = ztk_int32_to_string(a);

        ZtkConsole *console = ztk_console_new(runtime_context);
        ztk_console_write_text(console, temp1);
        ztk_console_write_text(console, temp2);

        z_object_unref(Z_OBJECT(console));
        z_object_unref(Z_OBJECT(temp2));
        z_object_unref(Z_OBJECT(temp1));
        z_object_unref(Z_OBJECT(b));
        z_object_unref(Z_OBJECT(a));
}

static void case6(ZRuntimeContext *runtime_context)
{
        /* Test #6: and */

        ZtkInt32 *a = ztk_int32_new(runtime_context);
        ztk_int32_set_value(a, 1);

        ZtkInt32 *b = ztk_int32_new(runtime_context);
        ztk_int32_set_value(b, 0);

        ZtkString *temp1 = ztk_int32_to_string(a);
        ztk_int32_and_operator(a, b);
        ZtkString *temp2 = ztk_int32_to_string(a);

        ZtkConsole *console = ztk_console_new(runtime_context);
        ztk_console_write_text(console, temp1);
        ztk_console_write_text(console, temp2);

        z_object_unref(Z_OBJECT(console));
        z_object_unref(Z_OBJECT(temp2));
        z_object_unref(Z_OBJECT(temp1));
        z_object_unref(Z_OBJECT(b));
        z_object_unref(Z_OBJECT(a));
}

static void case7(ZRuntimeContext *runtime_context)
{
        /* Test #7: not */

        ZtkInt32 *a = ztk_int32_new(runtime_context);
        ztk_int32_set_value(a, 1);

        ZtkString *temp1 = ztk_int32_to_string(a);
        ztk_int32_not_operator(a);
        ZtkString *temp2 = ztk_int32_to_string(a);
        ztk_int32_not_operator(a);
        ZtkString *temp3 = ztk_int32_to_string(a);

        ZtkConsole *console = ztk_console_new(runtime_context);
        ztk_console_write_text(console, temp1);
        ztk_console_write_text(console, temp2);
        ztk_console_write_text(console, temp3);

        z_object_unref(Z_OBJECT(console));
        z_object_unref(Z_OBJECT(temp3));
        z_object_unref(Z_OBJECT(temp2));
        z_object_unref(Z_OBJECT(temp1));
        z_object_unref(Z_OBJECT(a));
}

static void case8(ZRuntimeContext *runtime_context)
{
        /* Test #8: if-block */

        ZtkConsole *console = ztk_console_new(runtime_context);

        ZtkInt32 *a = ztk_int32_new(runtime_context);
        ztk_int32_set_value(a, 0);

        ztk_if(a, zero) {
                ZtkString *printout = ztk_int32_to_string(a);
                ztk_string_set_cstring(printout, "a is zero");
                ztk_console_write_text(console, printout);
                z_object_unref(Z_OBJECT(printout));

        } ztk_else_if(a, positive) {
                ZtkString *printout = ztk_int32_to_string(a);
                ztk_string_set_cstring(printout, "a is positive");
                ztk_console_write_text(console, printout);
                z_object_unref(Z_OBJECT(printout));

        } ztk_else_if(a, negative) {
                ZtkString *printout = ztk_int32_to_string(a);
                ztk_string_set_cstring(printout, "a is negative");
                ztk_console_write_text(console, printout);
                z_object_unref(Z_OBJECT(printout));

        } ztk_end_if(a);

        ztk_int32_set_value(a, -2);

        ztk_if(a, zero) {
                ZtkString *printout = ztk_int32_to_string(a);
                ztk_string_set_cstring(printout, "a is zero");
                ztk_console_write_text(console, printout);
                z_object_unref(Z_OBJECT(printout));

        } ztk_else_if(a, positive) {
                ZtkString *printout = ztk_int32_to_string(a);
                ztk_string_set_cstring(printout, "a is positive");
                ztk_console_write_text(console, printout);
                z_object_unref(Z_OBJECT(printout));

        } ztk_else_if(a, negative) {
                ZtkString *printout = ztk_int32_to_string(a);
                ztk_string_set_cstring(printout, "a is negative");
                ztk_console_write_text(console, printout);
                z_object_unref(Z_OBJECT(printout));

        } ztk_end_if(a);

        ztk_int32_set_value(a, 2);

        ztk_if(a, zero) {
                ZtkString *printout = ztk_int32_to_string(a);
                ztk_string_set_cstring(printout, "a is zero");
                ztk_console_write_text(console, printout);
                z_object_unref(Z_OBJECT(printout));

        } ztk_else_if(a, positive) {
                ZtkString *printout = ztk_int32_to_string(a);
                ztk_string_set_cstring(printout, "a is positive");
                ztk_console_write_text(console, printout);
                z_object_unref(Z_OBJECT(printout));

        } ztk_else_if(a, negative) {
                ZtkString *printout = ztk_int32_to_string(a);
                ztk_string_set_cstring(printout, "a is negative");
                ztk_console_write_text(console, printout);
                z_object_unref(Z_OBJECT(printout));

        } ztk_end_if(a);

        z_object_unref(Z_OBJECT(console));
        z_object_unref(Z_OBJECT(a));
}


static void case9(ZRuntimeContext *runtime_context)
{
        /* Test #9: while-loop */

        ZtkInt32 *step = ztk_int32_new(runtime_context);
        ztk_int32_set_value(step, 1);

        ZtkInt32 *iter = ztk_int32_new(runtime_context);
        ztk_int32_set_value(iter, -3);

        /* create the console */
        ZtkConsole *console = ztk_console_new(runtime_context);

        ztk_while(iter, negative) {

                /* create a JS variable and set its value to "Hello world" */
                ZtkString *msg = ztk_string_new(runtime_context);
                ztk_string_set_cstring(msg, "Hello world ");

                /* write the output to the console */
                ztk_console_write_text(console, msg);
                z_object_unref(Z_OBJECT(msg));

                ztk_int32_add(iter, step);

        } ztk_end_while(iter);

        z_object_unref(Z_OBJECT(console));
        z_object_unref(Z_OBJECT(iter));
        z_object_unref(Z_OBJECT(step));
}

void ztk_int32_test(struct zco_context_t *context, int id)
{
        /* JavaScript properties/methods for the Number object as an integer.

           toString:
                ztk_int32_to_string returns a base10 string representation of
                the number

           valueOf:
                This method is meaningless to the application.


           --------------------------------------------------------------------
           ZtkInt32 also supports these operations:

           add:
                ztk_int32_add performs the same operation as the += operator

           subtract:
                ztk_int32_subtract performs the same operation as the -= operator

           multiply:
                ztk_int32_multiply performs the same operation as the *= operator

           divide:
                ztk_int32_divide performs the same operation as the /= operator

           or:
                ztk_int32_or_operator performs the same operation as the |= operator

           and:
                ztk_int32_and_operator performs the same operation as the &= operator

           not:
                ztk_int32_not_operator performs the same operation as the ! unary operator

           --------------------------------------------------------------------
           ZtkInt32 can also be used as a flag for conditional jumps for if-blocks and loops.

           For if-blocks:

           ztk_if(the_var, nonzero) {
                // This will run if the_var (ZtkInt32 variable) is non-zero

           } ztk_else_if(the_var, zero) {
                // This will run if the_var is zero

           } ztk_end_if(the_var)


           For while-loops:

           ztk_while(the_var, negative) {

                // This block will run while the_var is < 0. Assuming 'x' is a ZtkInt32
                // with a positive value, it will be added to the_var every iteration
                // until the_var is no longer negative, at which point it will break
                // out of the loop.

                ztk_int32_add(the_var, x);

           } ztk_end_while(the_var);

         */

	DEFINE_TEST(1, case1, context, "32-bit Integer test #1: add");
	DEFINE_TEST(2, case2, context, "32-bit Integer test #2: subtract");
	DEFINE_TEST(3, case3, context, "32-bit Integer test #3: multiply");
	DEFINE_TEST(4, case4, context, "32-bit Integer test #4: divide");
	DEFINE_TEST(5, case5, context, "32-bit Integer test #5: or");
	DEFINE_TEST(6, case6, context, "32-bit Integer test #6: and");
	DEFINE_TEST(7, case7, context, "32-bit Integer test #7: not");
	DEFINE_TEST(8, case8, context, "32-bit Integer test #8: if-block");
	DEFINE_TEST(9, case9, context, "32-bit Integer test #9: while-loop");
}


