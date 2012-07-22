/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * signal-test.c: Test driver for signals
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
#include <z-test-object.h>
#include <z-c-closure-marshal.h>
#include <stdio.h>
#include <assert.h>

static struct zco_context_t context;

static int clicked(ZTestObject *self, void *userdata)
{
	printf("clicked signal emitted\n");
}

static void case1(void)
{
	ZTestObject *test_object = z_test_object_new(&context);

	z_object_connect(Z_OBJECT(test_object), "clicked", Z_OBJECT(test_object), "close1", NULL);
	z_object_connect(Z_OBJECT(test_object), "clicked", Z_OBJECT(test_object), "close2", NULL);
	z_test_object_click_it(test_object);
	z_object_unref(Z_OBJECT(test_object));
}

void signal_test(int id)
{
	ZCClosureMarshal *marshal;


	zco_context_init(&context);

	marshal = z_c_closure_marshal_new(&context);
	zco_context_set_marshal(&context, marshal);

	DEFINE_TEST(1, case1);


	z_object_unref(Z_OBJECT(marshal));
}
	
