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

#line 8 "z-file.zco"

#include <z-string.h>

#include <z-object-tracker.h>
#include <z-map.h>
#include <string.h>
#include <z-memory-allocator.h>
#include <z-file-protected.h>
#include <zco-context.h>
#include <stdlib.h>
#define Self ZFile
#define selfp (&self->_priv)
#define GET_NEW(ctx,allocator) __z_file_new(ctx,allocator)
#define INIT_EXISTS
#define init z_file_init
#define new z_file_new
#define open z_file_open
#define close z_file_close
#define write z_file_write
#define write_vformat z_file_write_vformat
#define write_format z_file_write_format

ZCO_DEFINE_CLASS_TYPE(z_file);

static void z_file_init(Self *self);
static void z_file_class_destroy(ZObjectGlobal *gbl);
static void z_file___delete(ZObject *self);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZFileGlobal * z_file_get_type(struct zco_context_t *ctx)
{
	ZCO_CREATE_CLASS(global, ZFile, z_file, 1);
	ZCO_INHERIT_CLASS(ZObject, z_object, ZFile);
	ZCO_REGISTER_TYPE(z_file);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZObject, z_object, z_file, class_destroy);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZObject, z_object, z_file, __delete);
	ZCO_CREATE_METHOD_MAP(ZFile, z_file);
	ZCO_REGISTER_METHOD(new);
	ZCO_REGISTER_METHOD(open);
	ZCO_REGISTER_METHOD(close);
	ZCO_REGISTER_METHOD(write);
	ZCO_REGISTER_METHOD(write_vformat);
	ZCO_REGISTER_METHOD(write_format);
	#ifdef GLOBAL_INIT_EXISTS
		global_init(global);
	#endif
	return global;
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
	ZCO_INIT_START(ZFile, z_file);
	__z_object_init(ctx, (ZObject *) (self));
	ZCO_SEAL_CLASS();
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
static void z_file_init(Self *self)
{
 selfp->file = NULL;
 }
Self * z_file_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator)
{
{
 Self *self = GET_NEW(ctx, allocator);
 return self;
 }
}
int  z_file_open(Self *self,const char *filename,const char *mode)
{
{
 selfp->file = fopen(filename, mode);
 return selfp->file? 0 : -1;
 }
}
int  z_file_close(Self *self)
{
{
 if (selfp->file) {
 fclose(selfp->file);
 selfp->file = NULL;
 return 0;
 }

 return -1;
 }
}
void  z_file_write(Self *self,const char *str)
{
{
 fputs(str, selfp->file);
 }
}
int  z_file_write_vformat(Self *self,const char *fmt,va_list ap)
{
{
 ZString *temp = z_string_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self));
 
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
}
void  z_file_write_format(Self *self,const char *fmt,...)
{
{
 va_list ap;

 va_start(ap, fmt);
 write_vformat(self, fmt, ap);
 va_end(ap);
 }
}
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_class_destroy
static void z_file_class_destroy(ZObjectGlobal *gbl)
{
	ZFileGlobal *_global = (ZFileGlobal *) gbl;
	#ifdef GLOBAL_DESTROY_EXISTS
		global_destroy(_global);
	#endif

}

#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent___delete
static void z_file___delete(ZObject *self)
{
	ZMemoryAllocator *allocator = CTX_FROM_OBJECT(self)->fixed_allocator;
	if (allocator)
		z_memory_allocator_deallocate_by_size(allocator, self, sizeof(Self));
	else
		free(self);
}

#undef PARENT_HANDLER



