/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * zco-app-context.h: Application level context management
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


#ifndef _ZCO_APP_CONTEXT_H_
#define _ZCO_APP_CONTEXT_H_

#include <zco-context.h>
#include <z-object.h>
#include <z-event-loop.h>

void zco_app_context_init(struct zco_context_t *ctx);
void zco_app_context_destroy(struct zco_context_t *ctx);

ZEventLoop * zco_app_context_get_event_loop(struct zco_context_t *ctx);

#endif

