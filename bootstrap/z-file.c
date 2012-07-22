/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-file.c: Bootstrap file for z-file.zco
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


#include <z-string.h>

#include <z-map.h>
#include <string.h>
#include <z-file.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZFile
#define selfp (&self->_priv)
#define GET_NEW(ctx) __z_file_new(ctx)
#define CTX self->_global->ctx
#define INIT_EXISTS
#line 14 "z-file.zco"
#define init z_file_init
#line 19 "z-file.zco"
#define new z_file_new
#line 25 "z-file.zco"
#define open z_file_open
#line 31 "z-file.zco"
#define close z_file_close
#line 42 "z-file.zco"
#define write z_file_write
#line 47 "z-file.zco"
#define write_vformat z_file_write_vformat
#line 64 "z-file.zco"
#define write_format z_file_write_format

int z_file_type_id = -1;

static Self *__z_file_new(struct zco_context_t *ctx)
{
	Self *self = (Self *) malloc(sizeof(Self));
	__z_file_init(ctx, self);
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
#line 14 "z-file.zco"
static void z_file_init(Self *self);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZFileGlobal * z_file_get_type(struct zco_context_t *ctx)
{
	void **global_ptr = NULL;
	if (z_file_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_file_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZFileGlobal *global = (ZFileGlobal *) malloc(sizeof(struct ZFileGlobal));
		global->ctx = ctx;
		global->_class = malloc(sizeof(struct ZFileClass));
		memset(global->_class, 0, sizeof(struct ZFileClass));
		global->name = "ZFile";
		global->vtable_off_list = NULL;
		global->vtable_off_size = 0;

		struct ZFile temp;

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
		if (z_file_type_id == -1)
			z_file_type_id = zco_allocate_type_id();
		global->id = z_file_type_id;
		zco_add_to_vtable(&global->vtable_off_list, &global->vtable_off_size, z_file_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_file_type_id);
		*global_ptr = global;
		
		__z_file_class_init(ctx, (ZFileClass *) global->_class);
		global->method_map = z_map_new(ctx);
		z_map_set_compare(global->method_map, __map_compare);
		z_map_set_key_destruct(global->method_map, (ZMapItemCallback) free);
#line 19 "z-file.zco"
		z_map_insert((ZMap *) global->method_map, strdup("new"), (ZObjectSignalHandler) new);
#line 25 "z-file.zco"
		z_map_insert((ZMap *) global->method_map, strdup("open"), (ZObjectSignalHandler) open);
#line 31 "z-file.zco"
		z_map_insert((ZMap *) global->method_map, strdup("close"), (ZObjectSignalHandler) close);
#line 42 "z-file.zco"
		z_map_insert((ZMap *) global->method_map, strdup("write"), (ZObjectSignalHandler) write);
#line 47 "z-file.zco"
		z_map_insert((ZMap *) global->method_map, strdup("write_vformat"), (ZObjectSignalHandler) write_vformat);
#line 64 "z-file.zco"
		z_map_insert((ZMap *) global->method_map, strdup("write_format"), (ZObjectSignalHandler) write_format);
		#ifdef GLOBAL_INIT_EXISTS
			global_init((ZFileGlobal *) global);
		#endif
		return global;
	}
	return (ZFileGlobal *) *global_ptr;
}

void __z_file_class_init(struct zco_context_t *ctx, ZFileClass *_class)
{
	__z_object_class_init(ctx, (ZObjectClass *) _class);
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_file_init(struct zco_context_t *ctx, Self *self)
{
	struct ZFileGlobal *_global = z_file_get_type(ctx);
	self->_global = _global;
	__z_object_init(ctx, (ZObject *) (self));
	((ZObject *) self)->class_base = (void *) _global->_class;
	((ZObject *) self)->global_base = (void *) _global;
	((ZObject *) self)->vtable = _global->vtable_off_list;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
#line 14 "z-file.zco"
static void z_file_init(Self *self)
{
 selfp->file = NULL;
 }
#line 19 "z-file.zco"
Self * z_file_new(struct zco_context_t *ctx)
{
 Self *self = GET_NEW(ctx);
 return self;
 }
#line 25 "z-file.zco"
int  z_file_open(Self *self,const char *filename,const char *mode)
{
 selfp->file = fopen(filename, mode);
 return selfp->file? 0 : -1;
 }
#line 31 "z-file.zco"
int  z_file_close(Self *self)
{
 if (selfp->file) {
 fclose(selfp->file);
 selfp->file = NULL;
 return 0;
 }

 return -1;
 }
#line 42 "z-file.zco"
void  z_file_write(Self *self,const char *str)
{
 fputs(str, selfp->file);
 }
#line 47 "z-file.zco"
int  z_file_write_vformat(Self *self,const char *fmt,va_list ap)
{
 ZString *temp = z_string_new(CTX);
 
 /* create a formatted string */
 z_string_append_vformat(temp, fmt, ap);

 /* write string to the file */
 z_string_validate(temp);
 char *s = z_string_get_cstring(temp, Z_STRING_ENCODING_UTF8);
 fputs(s, selfp->file);
 free(s);
 
 /* release temporary string */
 z_object_unref(Z_OBJECT(temp));
 }
#line 64 "z-file.zco"
void  z_file_write_format(Self *self,const char *fmt,...)
{
 va_list ap;

 va_start(ap, fmt);
 write_vformat(self, fmt, ap);
 va_end(ap);
 }


