#ifndef _Z_EVENT_LOOP_H_
#define _Z_EVENT_LOOP_H_
#line 4 "z-event-loop.zco"

#include <z-object.h>
#include <z-string.h>

#include <zco-type.h>
#define Self ZEventLoop
#define Z_EVENT_LOOP(s) ((ZEventLoop *) ((char *) (s) + (s)->_global->vtable_off_list[z_event_loop_type_id]))


struct ZEventLoopPrivate;
struct ZEventLoopProtected;
struct ZEventLoopGlobal;
struct ZEventLoopClass;
struct ZEventLoop;

typedef struct ZEventLoopPrivate ZEventLoopPrivate;
typedef struct ZEventLoopProtected ZEventLoopProtected;
typedef struct ZEventLoopGlobal ZEventLoopGlobal;
typedef struct ZEventLoopClass ZEventLoopClass;
typedef struct ZEventLoop ZEventLoop;

struct ZEventLoopPrivate {
};

struct ZEventLoopProtected {
};

struct ZEventLoopGlobal {
	int *vtable_off_list;
	int vtable_off_size;
	struct ZEventLoopClass *_class;
	struct zco_context_t *ctx;
	const char *name;
	int id;
	void *method_map;
};

struct ZEventLoopClass {
	struct ZObjectClass parent_z_object;
};

struct ZEventLoop {
	struct ZObject parent_z_object;
	struct ZEventLoopGlobal *_global;
	struct ZEventLoopPrivate _priv;
	struct ZEventLoopProtected _prot;
};
extern int z_event_loop_type_id;
ZEventLoopGlobal * z_event_loop_get_type(struct zco_context_t *ctx);
void __z_event_loop_init(struct zco_context_t *ctx, ZEventLoop *self);
void __z_event_loop_class_init(struct zco_context_t *ctx, ZEventLoopClass *_class);
#line 15 "z-event-loop.zco"
Self * z_event_loop_new(struct zco_context_t *ctx);
#line 22 "z-event-loop.zco"
void  z_event_loop_draw_event(Self *self,ZString *output);
#line 23 "z-event-loop.zco"
void  z_event_loop_io_event(Self *self);

#undef Self


#endif
