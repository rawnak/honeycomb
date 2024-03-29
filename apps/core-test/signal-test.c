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
#include <z-test-derived-object.h>
#include <z-c-closure-marshal.h>
#include <stdio.h>
#include <assert.h>


static int clicked(ZTestDerivedObject *self, void *userdata)
{
	trace("clicked signal emitted\n");
}

static void case1(struct zco_context_t *context)
{
	ZTestDerivedObject *test_object = z_test_derived_object_new(context, NULL);

        ZCClosureMarshal *marshal;
	marshal = z_c_closure_marshal_get_instance(context);
        z_object_set_closure_marshal(Z_OBJECT(test_object), Z_OBJECT(marshal));
	z_object_unref(Z_OBJECT(marshal));

	void *key1 = z_object_connect(Z_OBJECT(test_object), "clicked", Z_OBJECT(test_object), "close1", NULL);
	void *key2 = z_object_connect(Z_OBJECT(test_object), "clicked", Z_OBJECT(test_object), "close2", NULL);

	z_test_derived_object_click_it(test_object, "CLICK IT!!");

	z_object_disconnect(Z_OBJECT(test_object), "clicked", key2);
	z_object_disconnect(Z_OBJECT(test_object), "clicked", key1);

	z_object_unref(Z_OBJECT(test_object));
}

void signal_test(struct zco_context_t *context, int id)
{
	DEFINE_TEST(1, case1, context);
}
