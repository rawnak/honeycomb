#line 7 "z-event-loop.zco"


#include <z-map.h>
#include <string.h>
#include <z-event-loop.h>
#include <zco-type.h>
#include <stdlib.h>
#include <z-vector.h>
#include <z-value.h>
#define Self ZEventLoop
#define selfp (&self->_priv)
#define GET_NEW(ctx) __z_event_loop_new(ctx)
#define CTX self->_global->ctx
#define INIT_EXISTS
#line 11 "z-event-loop.zco"
#define init z_event_loop_init
#line 15 "z-event-loop.zco"
#define new z_event_loop_new
#line 22 "z-event-loop.zco"
#define draw_event z_event_loop_draw_event
#line 23 "z-event-loop.zco"
#define io_event z_event_loop_io_event

int z_event_loop_type_id = -1;

static Self *__z_event_loop_new(struct zco_context_t *ctx)
{
	Self *self = (Self *) malloc(sizeof(Self));
	__z_event_loop_init(ctx, self);
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
#line 11 "z-event-loop.zco"
static void z_event_loop_init(Self *self);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZEventLoopGlobal * z_event_loop_get_type(struct zco_context_t *ctx)
{
	void **global_ptr = NULL;
	if (z_event_loop_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_event_loop_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZEventLoopGlobal *global = (ZEventLoopGlobal *) malloc(sizeof(struct ZEventLoopGlobal));
		global->ctx = ctx;
		global->_class = malloc(sizeof(struct ZEventLoopClass));
		memset(global->_class, 0, sizeof(struct ZEventLoopClass));
		global->name = "ZEventLoop";
		global->vtable_off_list = NULL;
		global->vtable_off_size = 0;

		struct ZEventLoop temp;

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
		if (z_event_loop_type_id == -1)
			z_event_loop_type_id = zco_allocate_type_id();
		global->id = z_event_loop_type_id;
		zco_add_to_vtable(&global->vtable_off_list, &global->vtable_off_size, z_event_loop_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_event_loop_type_id);
		*global_ptr = global;
		
		__z_event_loop_class_init(ctx, (ZEventLoopClass *) global->_class);
		global->method_map = z_map_new(ctx);
		z_map_set_compare(global->method_map, __map_compare);
		z_map_set_key_destruct(global->method_map, (ZMapItemCallback) free);
#line 15 "z-event-loop.zco"
		z_map_insert((ZMap *) global->method_map, strdup("new"), (ZObjectSignalHandler) new);
		#ifdef GLOBAL_INIT_EXISTS
			global_init((ZEventLoopGlobal *) global);
		#endif
		return global;
	}
	return (ZEventLoopGlobal *) *global_ptr;
}

void __z_event_loop_class_init(struct zco_context_t *ctx, ZEventLoopClass *_class)
{
	__z_object_class_init(ctx, (ZObjectClass *) _class);
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_event_loop_init(struct zco_context_t *ctx, Self *self)
{
	struct ZEventLoopGlobal *_global = z_event_loop_get_type(ctx);
	self->_global = _global;
	__z_object_init(ctx, (ZObject *) (self));
	((ZObject *) self)->class_base = (void *) _global->_class;
	((ZObject *) self)->global_base = (void *) _global;
	((ZObject *) self)->vtable = _global->vtable_off_list;
#line 22 "z-event-loop.zco"
	z_object_register_signal(Z_OBJECT(self), "draw_event");
#line 23 "z-event-loop.zco"
	z_object_register_signal(Z_OBJECT(self), "io_event");
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
#line 11 "z-event-loop.zco"
static void z_event_loop_init(Self *self)
{
 }
#line 15 "z-event-loop.zco"
Self * z_event_loop_new(struct zco_context_t *ctx)
{
 Self *self = GET_NEW(ctx);
 return self;
 }
#line 22 "z-event-loop.zco"
void  z_event_loop_draw_event(Self *self,ZString *output)
#line 22 "z-event-loop.zco"
{
#line 22 "z-event-loop.zco"
	ZVector *args = z_vector_new(CTX, 0);
#line 22 "z-event-loop.zco"
	z_vector_set_item_destruct(args, (ZVectorItemCallback) z_object_unref);
#line 22 "z-event-loop.zco"
	{
#line 22 "z-event-loop.zco"
		ZValue *value = z_value_new(CTX);
#line 22 "z-event-loop.zco"
		z_value_set_as_object(value, Z_OBJECT(output));
#line 22 "z-event-loop.zco"
		z_vector_push_back(args, value);
#line 22 "z-event-loop.zco"
	}
#line 22 "z-event-loop.zco"
	z_object_emit_signal(Z_OBJECT(self), "draw_event", args);
#line 22 "z-event-loop.zco"
	z_object_unref(Z_OBJECT(args));
#line 22 "z-event-loop.zco"
}
#line 23 "z-event-loop.zco"
void  z_event_loop_io_event(Self *self)
#line 23 "z-event-loop.zco"
{
#line 23 "z-event-loop.zco"
	ZVector *args = z_vector_new(CTX, 0);
#line 23 "z-event-loop.zco"
	z_vector_set_item_destruct(args, (ZVectorItemCallback) z_object_unref);
#line 23 "z-event-loop.zco"
	z_object_emit_signal(Z_OBJECT(self), "io_event", args);
#line 23 "z-event-loop.zco"
	z_object_unref(Z_OBJECT(args));
#line 23 "z-event-loop.zco"
}

#line 24 "z-event-loop.zco"


