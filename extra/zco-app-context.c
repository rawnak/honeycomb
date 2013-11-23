/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * zco-app-context.c: Application level context management
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


#include <zco-app-context.h>
#include <z-framework-events.h>
#include <z-event-loop-linux.h>
#include <z-event-loop-posix.h>

void zco_app_context_init(struct zco_context_t *ctx)
{
        zco_context_init(ctx);
}

void zco_app_context_destroy(struct zco_context_t *ctx)
{
        /* Release the event loop. */
        ZEventLoop *event_loop = z_event_loop_get_instance_ptr(ctx);
        if (event_loop)
                z_object_unref(Z_OBJECT(event_loop));

        zco_context_destroy(ctx);
}

ZEventLoop * zco_app_context_get_event_loop_ptr(struct zco_context_t *ctx)
{
        ZEventLoop *event_loop = z_event_loop_get_instance_ptr(ctx);
        if (event_loop)
                return event_loop;

#ifdef USE_IO_EVENT_LOOP
        return (ZEventLoop *) z_event_loop_linux_new(ctx, NULL);
#else
        return (ZEventLoop *) z_event_loop_posix_new(ctx, NULL);
#endif
}

