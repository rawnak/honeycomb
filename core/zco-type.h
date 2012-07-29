/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * zco-type.h: Context management
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


#ifndef _ZCO_H_
#define _ZCO_H_

struct zco_context_t {
	void **types;
	int type_count;
	void *marshal;    /* ZClosureMarshal object */
	void *eventloop;  /* ZEventLoop object */
};

void    zco_context_init(struct zco_context_t *ctx);
void    zco_context_destroy(struct zco_context_t *ctx);
void    zco_context_set_marshal(struct zco_context_t *ctx, void *marshal);
void ** zco_get_ctx_type(struct zco_context_t *ctx, int type_id);
int     zco_allocate_type_id();
void    zco_inherit_vtable(int **list, int *size, int *src_list, int src_size, void *base, void *target);
void    zco_add_to_vtable(int **list, int *size, int type_id);
void *  zco_context_get_event_loop(struct zco_context_t *ctx);

#endif

