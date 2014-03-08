/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * network-test.c: Test driver for network
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

#include <zco-test.h>
#include <z-test-derived-object.h>
#include <z-c-closure-marshal.h>
#include <z-socket.h>
#include <z-server.h>
#include <z-bind-util.h>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

static int last_port = 4555;
static pthread_mutex_t port_lock = PTHREAD_MUTEX_INITIALIZER;

static ZServer * run_server(struct zco_context_t *context, ZBindHandler on_new_client, int port, int *stage)
{
        ZServer *server = z_server_new(context, NULL);
        ZBind *task;

        task = z_bind_util_create_c_bind(Z_OBJECT(server), on_new_client);
        z_bind_append_ptr(task, stage);
        z_server_set_on_new_client(server, task);
        z_object_unref(Z_OBJECT(task));

        z_server_start(server, port);
        return server;
}

static ZSocket * run_client(struct zco_context_t *context, ZBindHandler on_ready, int port, int *stage)
{
        ZSocket *client = z_socket_new(context, NULL);

        assert(*stage == 0);
        ++(*stage);

        z_socket_declare_family(client, AF_INET6);
        z_socket_set_ipv6_address(client, in6addr_any);
        z_socket_set_flowinfo(client, 0);

        ZBind *task;
        task = z_bind_util_create_c_bind(Z_OBJECT(client), on_ready);
        z_bind_append_ptr(task, client);
        z_bind_append_ptr(task, stage);
        z_socket_set_on_ready(client, task);
        z_object_unref(Z_OBJECT(task));

        trace("Client: Connecting to server\n");
        z_socket_set_port(client, port);
        z_socket_initiate_connection(client);

        return client;
}

static void send_message(ZSocket *socket, char *sender, char *msg)
{
        ZStream *stream = z_stream_new(CTX_FROM_OBJECT(socket), ALLOCATOR_FROM_OBJECT(socket));
        z_socket_connect_stream(socket, stream);

        ZString *message = z_string_new(CTX_FROM_OBJECT(socket), ALLOCATOR_FROM_OBJECT(socket));
        z_string_append_cstring(message, msg, Z_STRING_ENCODING_UTF8);
        z_stream_write_text(stream, message);
        z_object_unref(Z_OBJECT(message));

        z_object_unref(Z_OBJECT(stream));

        trace("%s says: %s\n", sender, msg);
}


static char * receive_message(ZSocket *socket, char *sender)
{
        char *buffer;

        ZStream *stream = z_stream_new(CTX_FROM_OBJECT(socket), ALLOCATOR_FROM_OBJECT(socket));
        z_socket_connect_stream(socket, stream);

        ZString *text = z_stream_read_text(stream);
        z_object_unref(Z_OBJECT(stream));

        if (!text || z_string_get_length(text) == 0) {
                buffer = malloc(1);
                buffer[0] = 0;

                if (text)
                        z_object_unref(Z_OBJECT(text));

                return buffer;
        }

        buffer = z_string_get_cstring(text, Z_STRING_ENCODING_UTF8);

        trace("== %s received '%s' (len=%d)\n", sender, buffer, z_string_get_length(text));
        z_object_unref(Z_OBJECT(text));

        return buffer;
}

static void server_close_connection1(ZBind *task, ZSocket *socket, int *stage)
{
        assert(*stage == 6);
        ++(*stage);

        trace("Server: Connection closed by peer\n");
        trace("Server: Disconnecting client\n");
        z_socket_shutdown_outgoing(socket);
}

static void server_hangup_connection1(ZBind *task, ZSocket *socket, int *stage)
{
        assert(*stage == 10);
        ++(*stage);

        trace("Server: Connection hangup!\n");
        ZEventLoop *ev = zco_app_context_get_event_loop_ptr(CTX_FROM_OBJECT(task));
        z_event_loop_quit(ev);

        z_object_unref(Z_OBJECT(socket));
}

static void server_error_connection1(ZBind *task, ZSocket *socket, int *stage)
{
        trace("Server: Connection error!\n");
        abort();
}

static void server_message_handler1(ZBind *task, ZSocket *socket, int *stage)
{
        char *msg = receive_message(socket, "Server");
        if (!strcmp(msg, "Hi")) {
                assert(*stage == 3);
                ++(*stage);

                send_message(socket, "Server", "Hello");
        } else {
                assert(*stage == 5);
                ++(*stage);
        }

        free(msg);
}

static void client_close_connection1(ZBind *task, ZSocket *socket, int *stage)
{
        assert(*stage == 8);
        ++(*stage);

        trace("Client: Connection closed.\n");
}

static void client_hangup_connection1(ZBind *task, ZSocket *socket, int *stage)
{
        assert(*stage == 9);
        ++(*stage);

        trace("Client: Connection hangup!\n");
        z_object_unref(Z_OBJECT(socket));
}

static void client_error_connection1(ZBind *task, ZSocket *socket, int *stage)
{
        trace("Connection error!\n");
        abort();
}

static void client_message_handler1(ZBind *task, ZSocket *socket, int *stage)
{
        char *msg = receive_message(socket, "Client");
        if (!strcmp(msg, "Hello")) {
                assert(*stage == 4);
                ++(*stage);

                trace("Client: Disconnecting from server\n");
                z_socket_shutdown_outgoing(socket);
        } else {
                assert(*stage == 7);
                ++(*stage);
        }

        free(msg);
}

static void on_new_client1(ZBind *task, int *stage, ZSocket *socket, ZServer *server)
{
        trace("Server: New client connected\n");

        assert(*stage == 1);
        ++(*stage);

        task = z_bind_util_create_c_bind(Z_OBJECT(socket), (ZBindHandler) server_message_handler1);
        z_bind_append_ptr(task, socket);
        z_bind_append_ptr(task, stage);
        z_socket_set_on_readable(socket, task);
        z_object_unref(Z_OBJECT(task));

        task = z_bind_util_create_c_bind(Z_OBJECT(socket), (ZBindHandler) server_close_connection1);
        z_bind_append_ptr(task, socket);
        z_bind_append_ptr(task, stage);
        z_socket_set_on_disconnect(socket, task);
        z_object_unref(Z_OBJECT(task));

        task = z_bind_util_create_c_bind(Z_OBJECT(socket), (ZBindHandler) server_hangup_connection1);
        z_bind_append_ptr(task, socket);
        z_bind_append_ptr(task, stage);
        z_socket_set_on_hangup(socket, task);
        z_object_unref(Z_OBJECT(task));

        task = z_bind_util_create_c_bind(Z_OBJECT(socket), (ZBindHandler) server_error_connection1);
        z_bind_append_ptr(task, socket);
        z_bind_append_ptr(task, stage);
        z_socket_set_on_error(socket, task);
        z_object_unref(Z_OBJECT(task));

        z_object_unref(Z_OBJECT(server));
}

static void on_client_ready1(ZBind *task, ZSocket *socket, int *stage)
{
        trace("Client: Connection established\n");

        assert(*stage == 2);
        ++(*stage);

        task = z_bind_util_create_c_bind(Z_OBJECT(socket), (ZBindHandler) client_close_connection1);
        z_bind_append_ptr(task, socket);
        z_bind_append_ptr(task, stage);
        z_socket_set_on_disconnect(socket, task);
        z_object_unref(Z_OBJECT(task));

        task = z_bind_util_create_c_bind(Z_OBJECT(socket), (ZBindHandler) client_hangup_connection1);
        z_bind_append_ptr(task, socket);
        z_bind_append_ptr(task, stage);
        z_socket_set_on_hangup(socket, task);
        z_object_unref(Z_OBJECT(task));

        task = z_bind_util_create_c_bind(Z_OBJECT(socket), (ZBindHandler) client_error_connection1);
        z_bind_append_ptr(task, socket);
        z_bind_append_ptr(task, stage);
        z_socket_set_on_error(socket, task);
        z_object_unref(Z_OBJECT(task));

        task = z_bind_util_create_c_bind(Z_OBJECT(socket), (ZBindHandler) client_message_handler1);
        z_bind_append_ptr(task, socket);
        z_bind_append_ptr(task, stage);
        z_socket_set_on_readable(socket, task);
        z_object_unref(Z_OBJECT(task));

        send_message(socket, "Client", "Hi");
}

static void case1(struct zco_context_t *context, int *stage)
{
        pthread_mutex_lock(&port_lock);

        run_server(context, (ZBindHandler) on_new_client1, last_port, stage);
        run_client(context, (ZBindHandler) on_client_ready1, last_port, stage);

        ++last_port;

        pthread_mutex_unlock(&port_lock);
}

static void application_main(ZBind *task, int id, int *stage)
{
        struct zco_context_t *context = CTX_FROM_OBJECT(task);
        DEFINE_TEST(1, case1, context, stage);
}

void network_test(struct zco_context_t *context, int id)
{
        int i, first, last;

        if (id == 0) {
                first = 1;
                last = 1;
        } else {
                first = id;
                last = id;
        }

        for (int i=first; i<=last; ++i) {
                /* Create a guest thread in which the client & server will run */
                struct zco_context_t app_ctx;
                zco_app_context_init(&app_ctx);

                ZEventLoop *ev = zco_app_context_get_event_loop_ptr(&app_ctx);
                z_event_loop_set_name(ev, "Application");
                z_event_loop_run(ev);

                /* Initialize the stage counter */
                int *stage = malloc(sizeof(int));
                *stage = 0;

                /* Call application_main() on the guest thread */
                ZBind *task = z_bind_new(context, NULL);
                z_bind_set_handler(task, (ZBindHandler) application_main);
                z_bind_append_int32(task, id);
                z_bind_append_ptr(task, stage);
                z_event_loop_post_task(ev, task, NULL, 0, 0);
                z_object_unref(Z_OBJECT(task));

                /* Wait for event loop to quit */
                z_event_loop_join(ev);

                /* Verify that 'stage' is the correct value */
                assert(*stage == 11);
                free(stage);

                zco_app_context_destroy(&app_ctx);
        }
}

