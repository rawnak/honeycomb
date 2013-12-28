/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * z-bind-util.h: Utilities around Bind
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


#ifndef Z_BIND_UTIL
#define Z_BIND_UTIL

#include <z-bind.h>

ZBind *create_c_bind(ZObject *ref_object, ZBindHandler handler);

#endif

