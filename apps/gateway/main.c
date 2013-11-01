/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * main.c: FastCGI client main
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


#include <z-gateway-application.h>
#include <z-map.h>
#include <fcgi_config.h>
#include <fcgiapp.h>
#include <sys/resource.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern char **environ;

static char random_state[256];

static void generate_guid(union guid_t *guid)
{
	guid->f32[0] = random();
	guid->f32[1] = random();
	guid->f32[2] = random();
	guid->f32[3] = random();
}

static char * get_session_guid(const char *http_cookie)
{
	int is_done = 0;
	char *temp_http_cookie;
	char *start, *p;
	char *name = NULL, *value = NULL;

	temp_http_cookie = strdup(http_cookie);
	start = temp_http_cookie;
	p = temp_http_cookie;

	while (!is_done) {
		switch(*p)
		{
		case '=':
			name = start;
			*p = 0;
			start = p = p + 1;
			break;
		case 0:
			is_done = 1;
		case ';':
			value = start;
			*p = 0;
			start = p = p + 2;

			if (name && !strcmp(name, "ZCOSESSID")) {
				free(temp_http_cookie);
				return strdup(value);
			}
			break;
		default:
			++p;
			break;
		}
	}

	free(temp_http_cookie);
	return NULL;
}

static int hex_to_byte(const char *hex)
{
	int byte;
	char ch;

	/* high nibble */
	ch = hex[0];

	if (ch >= '0' && ch <= '9')
		byte = ((ch - '0') & 0xf) << 4;

	else if (ch >= 'a' && ch <= 'f')
		byte = ((ch - 'a' + 10) & 0xf) << 4;

	else
		return -1;

	/* low nibble */
	ch = hex[1];

	if (ch >= '0' && ch <= '9')
		byte |= (ch - '0') & 0xf;

	else if (ch >= 'a' && ch <= 'f')
		byte |= (ch - 'a' + 10) & 0xf;

	else
		return -1;


	return byte;
}

static void byte_to_hex(char *hex, int byte)
{
	unsigned char nibble;

	/* high nibble */
	nibble = byte >> 4;

	if (nibble >= 0 && nibble <= 9)
		hex[0] = '0' + nibble;
	else 
		hex[0] = 'a' + nibble - 10;


	/* low nibble */
	nibble = byte & 0xf;

	if (nibble >= 0 && nibble <= 9)
		hex[1] = '0' + nibble;
	else 
		hex[1] = 'a' + nibble - 10;
}

static int guid_from_string(union guid_t *guid, const char *str)
{
	int i;

	/* verify str is not NULL */
	if (!str)
		return -1;

	/* verify guid is of the right length */
	for (i=0; i<16; ++i) {
		int byte = hex_to_byte(str + (i*2));

		if (byte == -1) {
			printf("byte at %d is bad: %s\n", i, str + (i*2));
			return -1;
		}

		guid->f8[i] = (unsigned char) byte;
	}

	return 0;
}

static void guid_to_string(const union guid_t *guid, char *str)
{
	int i;

	for (i=0; i<16; ++i) {
		int byte = guid->f8[i];
		byte_to_hex(str + (i*2), byte);
	}

	str[32] = 0;
}

static void enable_core_dump()
{
	struct rlimit _limit;

	/* enable core dump */
	_limit.rlim_cur = RLIM_INFINITY;
	_limit.rlim_max = RLIM_INFINITY;
	setrlimit(RLIMIT_CORE, &_limit);
}

static void seed_randomizer()
{
	/* initialize the random number generator */
	initstate(time(NULL), random_state, sizeof(random_state));
	setstate(random_state);
}

static int guid_compare(ZMap *self, const void *_a, const void *_b)
{
	union guid_t *a = (union guid_t *) _a;
	union guid_t *b = (union guid_t *) _b;

	if (a->f64[0] < b->f64[0])
		return -1;

	else if (a->f64[0] > b->f64[0])
		return 1;

	else if (a->f64[1] < b->f64[1])
		return -1;

	else if (a->f64[1] > b->f64[1])
		return 1;

	else
		return 0;
}

static void session_destroy(ZGatewayApplication *app)
{
	/* keep a reference to the context object */
	struct zco_context_t *context = z_gateway_application_get_context(app);

	/* free the application data */
	z_object_unref(Z_OBJECT(app));

	/* destroy the context */
	zco_app_context_destroy(context);
	free(context);
}

int main(int argc, char **argv)
{
	FCGX_Stream *in, *out, *err;
	FCGX_ParamArray envp;
	struct zco_context_t root_context;
	ZMap *sessions;
	
	/* enable core dump if process crashes */
	enable_core_dump();

	/* seed the randomizer based on the current time */
	seed_randomizer();

	/* prepare the root context */
	zco_app_context_init(&root_context);
	sessions = z_map_new(&root_context, NULL);
	
	z_map_set_key_destruct(sessions, (ZMapItemCallback) free);
	z_map_set_value_destruct(sessions, (ZMapItemCallback) session_destroy);
	z_map_set_compare(sessions, guid_compare);

	while (FCGX_Accept(&in, &out, &err, &envp) >= 0) {
		FCGX_FPrintF(out, "Content-type: text/html\r\n");

		/* get HTTP cookies */
		char *http_cookie = FCGX_GetParam("HTTP_COOKIE", envp);
		char *session_guid = NULL;

		/* look for a session cookie */
		if (http_cookie)
			session_guid = get_session_guid(http_cookie);

		/* extract guid from the session guid cookie string */
		union guid_t guid;

		if (!session_guid || guid_from_string(&guid, session_guid) != 0) {
			/* session guid does not exist or is invalid. lets generate a new one */
			session_guid = realloc(session_guid, 33);
			generate_guid(&guid);

			/* stringify the guid */
			guid_to_string(&guid, session_guid);

			/* write session guid into HTTP header */
			FCGX_FPrintF(out, "Set-Cookie: ZCOSESSID=%s\r\n", session_guid);
		}

		free(session_guid);

		/* look up the session guid in the sessions map */
		ZGatewayApplication *app;
		ZMapIter *it = z_map_find(sessions, &guid);

		if (it) {
			app = (ZGatewayApplication *) z_map_get_value(sessions, it);
			z_object_unref(Z_OBJECT(it));

		} else {
			/* create a new context */
			struct zco_context_t *context = malloc(sizeof(struct zco_context_t));
			zco_app_context_init(context);

			/* create a new ZGatewayApplication */
			app = z_gateway_application_new(context, NULL);

			/* insert ZGatewayApplication into the session map */
			union guid_t *guid_copy = malloc(sizeof(union guid_t));
			memcpy(guid_copy, &guid, sizeof(union guid_t));
			z_map_insert(sessions, guid_copy, app);
		}

		z_gateway_application_process_request(app, in, out, envp);

		/* release expired sessions */
		if (!z_map_get_is_empty(sessions)) {
			it = z_map_get_begin(sessions);
			ZMapIter *end = z_map_get_end(sessions);

			while (!z_map_iter_is_equal(it, end)) {
				app = (ZGatewayApplication *) z_map_get_value(sessions, it);

				if (z_gateway_application_get_is_expired(app)) {
					z_map_erase1_inc(sessions, &it);
					z_map_iter_decrement(end);
				} else {
					z_map_iter_increment(it);
				}
			}

			z_object_unref(Z_OBJECT(it));
			z_object_unref(Z_OBJECT(end));
		}
	}

	z_object_unref(Z_OBJECT(sessions));
	zco_app_context_destroy(&root_context);

	return 0;
}


