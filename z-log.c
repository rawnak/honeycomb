/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-log.c: Bootstrap file for z-log.zco
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


#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include <strings.h>

static int is_initialized = 0;
static int debug_mode = 0;
static int backtrace_level = 1;


#include <string.h>
#include <z-log.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZLog
#define selfp (&self->_priv)
#define GET_NEW(ctx) __z_log_new(ctx)
#define CTX self->_global->ctx
#line 49 "z-log.zco"
#define show_backtrace z_log_show_backtrace
#line 68 "z-log.zco"
#define initialize z_log_initialize
#line 84 "z-log.zco"
#define trace z_log_trace

int z_log_type_id = -1;
static ZLogGlobal * z_log_global;

static Self *__z_log_new(struct zco_context_t *ctx)
{
	Self *self = (Self *) malloc(sizeof(Self));
	__z_log_init(ctx, self);
	return self;
}
#line 49 "z-log.zco"
static void  z_log_show_backtrace();
#line 68 "z-log.zco"
static void  z_log_initialize();

ZLogGlobal * z_log_get_type(struct zco_context_t *ctx)
{
	if (z_log_type_id == -1)
		z_log_type_id = zco_allocate_type_id();

	void **global_ptr = zco_get_ctx_type(ctx, z_log_type_id);
	if (*global_ptr == 0) {
		*global_ptr = malloc(sizeof(struct ZLogGlobal));
		struct ZLogGlobal *global = (ZLogGlobal *) *global_ptr;
		z_log_global = global;
		global->ctx = ctx;
		global->_class = malloc(sizeof(struct ZLogClass));
		memset(global->_class, 0, sizeof(struct ZLogClass));
		global->name = "ZLog";
		global->id = z_log_type_id;
		global->vtable_off_list = NULL;
		global->vtable_off_size = 0;

		struct ZLogClass temp;

		{
			struct ZObjectGlobal *p_class = z_object_get_type(ctx);
			zco_inherit_vtable(
				&global->vtable_off_list,
				&global->vtable_off_size,
				p_class->vtable_off_list,
				p_class->vtable_off_size,
				&temp,
				&temp.parent_z_object);
			unsigned long offset = global->vtable_off_list[z_object_type_id];
			memcpy((char *) global->_class + offset, p_class->_class, sizeof(struct ZObjectClass));
		}
		zco_add_to_vtable(&global->vtable_off_list, &global->vtable_off_size, z_log_type_id);		
		#ifdef CLASS_INIT_EXISTS
			class_init((ZLogGlobal *) global);
		#endif
	}
	return (ZLogGlobal *) *global_ptr;
}

void __z_log_init(struct zco_context_t *ctx, Self *self)
{
	struct ZLogGlobal *_global = z_log_get_type(ctx);
	self->_global = _global;
	__z_object_init(ctx, Z_OBJECT(self));
	((ZObject *) self)->class_base = (void *) _global->_class;
	((ZObject *) self)->vtable = _global->vtable_off_list;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
#line 49 "z-log.zco"
static void  z_log_show_backtrace()
{
 void *buffer[100];
 void **p;
 int count;

 /* get the backtrace */
 count = backtrace(buffer, 100);

 /* skip the first two functions since they are redundant */
 p = buffer;
 p = buffer + 2;
 count -= 2;

 /* print the back trace */
 backtrace_symbols_fd(p, count, 2);
 fprintf(stderr, "\n");
 }
#line 68 "z-log.zco"
static void  z_log_initialize()
{
 if (is_initialized)
 return;

 /* check to see if Z_DEBUG environment variable is set */
 char *val = getenv("Z_DEBUG");
 if (val && (!strcmp(val, "1") || !strcasecmp(val, "on") || !strcasecmp(val, "true") || !strcasecmp(val, "yes")))
 debug_mode = 1;
 else
 debug_mode = 0;

 /* enable backtrace */
 backtrace_level = 1;
 }
#line 84 "z-log.zco"
void  z_log_trace(int level,const char *filename,int line_number,const char *caller_name,const char *fmt,...)
{
 va_list ap;
 va_start(ap, fmt);

 initialize();

 switch (level) {
 case ZLogMessage:
 fprintf(stderr, "** message ** %s:%d: %s: ", filename, line_number, caller_name);
 vfprintf(stderr, fmt, ap);
 fprintf(stderr, "\n");
 break;

 case ZLogWarning:
 fprintf(stderr, "** warning ** %s:%d: %s: ", filename, line_number, caller_name);
 vfprintf(stderr, fmt, ap);
 fprintf(stderr, "\n");

 if (debug_mode) {
 if (backtrace_level == 1)
 show_backtrace();

 abort();
 }
 break;

 case ZLogCritical:
 fprintf(stderr, "** critical warning ** %s:%d: %s: ", filename, line_number, caller_name);
 vfprintf(stderr, fmt, ap);
 fprintf(stderr, "\n");

 if (backtrace_level == 1)
 show_backtrace();

 if (debug_mode)
 abort();
 break;

 case ZLogError:
 fprintf(stderr, "** fatal error ** %s:%d: %s: ", filename, line_number, caller_name);
 vfprintf(stderr, fmt, ap);
 fprintf(stderr, "\n");

 if (backtrace_level == 1)
 show_backtrace();

 abort();
 break;

 case ZLogDebug:
 if (debug_mode) {
 fprintf(stderr, "** debug ** %s:%d: %s: ", filename, line_number, caller_name);
 vfprintf(stderr, fmt, ap);
 fprintf(stderr, "\n");

 if (backtrace_level == 1)
 show_backtrace();
 }
 break;
 }

 va_end(ap);
 }



