/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * zco.c: Context management
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

#include <zco.h>

static struct zco_context_t *contexts = 0;
static struct zco_context_t **free_contexts = 0;
static int context_count = 0;
static int free_context_count = 0;
static int max_free_context_count = 0;
static int type_count = 0;

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

   /* add the given context ID into the free list */
   free_contexts[free_countext_count-1] = ctx;
}

void ** zco_get_ctx_type(struct zc_context_t *ctx, int type_id)
{
   if (type_id >= ctx->type_count) {
      ctx->type_count = type_id + 1;
      ctx->types = realloc(ctx->types, sizeof(void *) * ctx->type_count);
      ctx->types[type_id] = 0;
   }

   return ctx->types + type_id;
}

int zco_allocate_type_id()
{
   /* type ID starts with 0 */
   return type_count++;
}

