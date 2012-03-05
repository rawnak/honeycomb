/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * zco-type.c: Context management
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

#include <zco-type.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static int next_id = -1;

void zco_context_init(struct zco_context_t *ctx)
{
	ctx->type_count = 0;
	ctx->types = 0;
}

void **zco_get_ctx_type(struct zco_context_t *ctx, int type_id)
{
	if (ctx->type_count <= type_id) {
		int new_size = type_id + 1;

		ctx->types = (void **) realloc(ctx->types, new_size * sizeof(void *));
		memset(ctx->types + ctx->type_count, 0, (new_size - ctx->type_count) * sizeof(void *));
		ctx->type_count = new_size;
	}

	return ctx->types + type_id;
}

int zco_allocate_type_id()
{
	return ++next_id;
}

void zco_inherit_vtable(int **list, int *size, int *src_list, int src_size, void *base, void *target)
{
	int i;

	/* compute the difference between the two address and store the offset into this element */
	int offset = (unsigned long) target - (unsigned long) base;

	/* if the source table is larger than the target table, increase the size of the target table
	   to match that of the source table */
	if (*size < src_size) {
		int old_size = *size;
		*size = src_size;

		*list = (int *) realloc(*list, src_size * sizeof(int));

		/* fill the uninitialized elements with -1 */
		memset(*list + old_size, 0xff, (src_size - old_size) * sizeof(int));
	} 

	/* copy the valid elements from the source table to the target table */
	for (i=0; i<src_size; ++i) {
		int src = src_list[i];

		if (src != -1)
			(*list)[i] = src_list[i] + offset;
	}
}

void zco_add_to_vtable(int **list, int *size, int type_id)
{
	/* if the type_id that we want to add is too high for the current size of the table, increase
	   the size of the table so that we are able to add this new type_id */
	if (*size <= type_id) {
		/* current vtable_off_table isn't large enough to hold specified type. we need to
		   resize the table and set the uninitialized data to -1 */
		int old_size = *size;
		int new_size = type_id + 1;
		*size = new_size;

		*list = (int *) realloc(*list, new_size * sizeof(int));

		/* fill the uninitialized elements (all new elements except for the last one, which we want
		   to fill with useful information) with -1 */
		memset(*list + old_size, 0xff, (new_size - old_size - 1) * sizeof(int));
	}

	/* set the offset of the type 'type_id' to 0 */
	(*list)[type_id] = 0;
}

#if 0
static struct zco_context_t *contexts = 0;
static struct zco_context_t **free_contexts = 0;
static int context_count = 0;
static int free_context_count = 0;
static int max_free_context_count = 0;

struct zco_context_t * zco_allocate_ctx()
{
   struct zco_context_t *ctx;

   if (free_context_count > 0) {
      /* if there are contexts in the free list, pop the latest one */
      --free_context_count;
      ctx = free_contexts[free_context_count];

   } else {
      /* if no contexts are in the free list, allocate a new one */
      ++context_count;
      contexts = realloc(contexts, sizeof(struct zco_context_t) * context_count);
      ctx = contexts + (context_count-1);
   }

   ctx->types = NULL;
   ctx->type_count = 0;

   return ctx;
}

void zco_free_ctx(struct zco_context_t *ctx)
{
   /* increase the size of the free context list */
   ++free_context_count;

   if (max_free_context_count < free_context_count) {
      max_free_context_count = free_context_count;
      free_contexts = realloc(free_contexts, sizeof(struct zco_context_t *) * max_free_context_count);
   }


void zco_free_ctx(struct zco_context_t *ctx)
{
   /* increase the size of the free context list */
   ++free_context_count;

   if (max_free_context_count < free_context_count) {
      max_free_context_count = free_context_count;
      free_contexts = realloc(free_contexts, sizeof(struct zco_context_t *) * max_free_context_count);
   }

   /* add the given context ID into the free list */
   free_contexts[free_countext_count-1] = ctx;
}

#endif

