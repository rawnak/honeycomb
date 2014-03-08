/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * zco-toolkit-test.h: Toolkit test main
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

#ifndef _ZCO_TOOLKIT_TEST_H_
#define _ZCO_TOOLKIT_TEST_H_

#include <z-runtime-context.h>

#ifndef _SYS_CDEFS_H
#include <sys/cdefs.h>
#endif

/* convenience macro */
#define DEFINE_TEST(id_num,callback,ctx,title) if(id==0 || id==id_num) { define_test(callback,ctx,title); }

void define_test(void(*callback)(ZRuntimeContext *), struct zco_context_t *ctx, const char *title);

void ztk_string_test(struct zco_context_t *, int);
void ztk_int32_test(struct zco_context_t *, int);

#endif
