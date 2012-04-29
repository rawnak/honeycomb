/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-log.h: Bootstrap file for z-log.zco
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

#ifndef _Z_LOG_H_
#define _Z_LOG_H_

#include <z-object.h>
#include <stdarg.h>
#include <sys/cdefs.h>

/* @brief prints a log message */
#define z_message(...) (z_log_trace(ZLogMessage, __FILE__, __LINE__, __func__, __VA_ARGS__))

/* @brief prints a warning message. setting Z_DEBUG environment variable will
          make warnings abort the process */
#define z_warning(...) (z_log_trace(ZLogWarning, __FILE__, __LINE__, __func__, __VA_ARGS__))

/* @brief prints a critical warning message. setting Z_DEBUG environment
          variable will make warnings abort the process */
#define z_critical(...) (z_log_trace(ZLogCritical, __FILE__, __LINE__, __func__, __VA_ARGS__))

/* @brief prints an error message. this will always abort the process */
#define z_error(...) (z_log_trace(ZLogError, __FILE__, __LINE__, __func__, __VA_ARGS__))

/* @brief prints a debug message if Z_DEBUG environment variable is set */
#define z_debug(...) (z_log_trace(ZLogDebug, __FILE__, __LINE__, __func__, __VA_ARGS__))

/* @brief prints an error message if the expression is FALSE. this will always abort the process */
#define z_assert(expr) ((likely(expr))? (void)(0) : z_error("Assertion '%s' failed", __STRING(expr)))

enum ZLogType {
 ZLogMessage,
 ZLogWarning,
 ZLogCritical,
 ZLogError,
 ZLogDebug
};

#include <zco-type.h>
#define Self ZLog
#define Z_LOG(s) ((ZLog *) (s))


struct ZLogPrivate;
struct ZLogProtected;
struct ZLogGlobal;
struct ZLogClass;
struct ZLog;

typedef struct ZLogPrivate ZLogPrivate;
typedef struct ZLogProtected ZLogProtected;
typedef struct ZLogGlobal ZLogGlobal;
typedef struct ZLogClass ZLogClass;
typedef struct ZLog ZLog;

struct ZLogPrivate {
};

struct ZLogProtected {
};

struct ZLogGlobal {
	int *vtable_off_list;
	int vtable_off_size;
	struct ZLogClass *_class;
	struct zco_context_t *ctx;
	const char *name;
	int id;
};

struct ZLogClass {
	struct ZObjectClass parent_z_object;
};

struct ZLog {
	struct ZObject parent_z_object;
	struct ZLogGlobal *_global;
	struct ZLogPrivate _priv;
	struct ZLogProtected _prot;
};
extern int z_log_type_id;
ZLogGlobal * z_log_get_type(struct zco_context_t *ctx);
void __z_log_init(struct zco_context_t *ctx, ZLog *self);
#line 84 "z-log.zco"
void  z_log_trace(int level,const char *filename,int line_number,const char *caller_name,const char *fmt,...);

#undef Self


#endif
