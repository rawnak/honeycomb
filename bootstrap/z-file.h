/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-file.h: Bootstrap file for z-file.zco
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

#ifndef _Z_FILE_H_
#define _Z_FILE_H_
#line 4 "z-file.zco"

#include <z-object.h>
#include <stdio.h>

#include <zco-type.h>
#define Self ZFile
#define Z_FILE(s) ((ZFile *) ((char *) (s) + GLOBAL_FROM_OBJECT(s)->common.vtable_off_list[z_file_type_id]))


struct ZFilePrivate;
struct ZFileProtected;
struct ZFileGlobal;
struct ZFileClass;
struct ZFile;

typedef struct ZFilePrivate ZFilePrivate;
typedef struct ZFileProtected ZFileProtected;
typedef struct ZFileGlobal ZFileGlobal;
typedef struct ZFileClass ZFileClass;
typedef struct ZFile ZFile;

struct ZFilePrivate {
#line 12 "z-file.zco"
	FILE * file;
};

struct ZFileProtected {
};

struct ZFileGlobal {
	struct ZCommonGlobal common;
	struct ZFileClass *_class;
#line 73 "z-file.zco"
	void (*__parent_class_destroy)(ZObjectGlobal *gbl);
};

struct ZFileClass {
	struct ZObjectClass parent_z_object;
};

struct ZFile {
	struct ZObject parent_z_object;
	struct ZFileGlobal *_global;
	struct ZFilePrivate _priv;
	struct ZFileProtected _prot;
};
extern int z_file_type_id;
ZFileGlobal * z_file_get_type(struct zco_context_t *ctx);
void __z_file_init(struct zco_context_t *ctx, ZFile *self);
void __z_file_class_init(struct zco_context_t *ctx, ZFileClass *_class);
#line 19 "z-file.zco"
Self * z_file_new(struct zco_context_t *ctx);
#line 25 "z-file.zco"
int  z_file_open(Self *self,const char *filename,const char *mode);
#line 31 "z-file.zco"
int  z_file_close(Self *self);
#line 42 "z-file.zco"
void  z_file_write(Self *self,const char *str);
#line 47 "z-file.zco"
int  z_file_write_vformat(Self *self,const char *fmt,va_list ap);
#line 64 "z-file.zco"
void  z_file_write_format(Self *self,const char *fmt,...);

#undef Self


#endif
