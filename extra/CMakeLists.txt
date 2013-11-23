cmake_minimum_required(VERSION 2.8)
set(CMAKE_VERBOSE_MAKEFILE OFF)
project(extra)

find_package(BISON)
find_package(FLEX)
include_directories(
      ${CMAKE_SOURCE_DIR}/core	       # core header files
      ${CMAKE_BINARY_DIR}/core	       # generated core header files
      ${CMAKE_SOURCE_DIR}/extra	       # extra header files
      ${CMAKE_CURRENT_BINARY_DIR}      # generated widget header files
      /usr/lib/libffi-3.0.13/include   # libffi
      )

macro(parse_zco OBJECT_NAME)
	add_custom_command(
	      OUTPUT ${OBJECT_NAME}.h ${OBJECT_NAME}.c
	      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/${OBJECT_NAME}.zco ${CMAKE_CURRENT_BINARY_DIR}/
	      COMMAND ${CMAKE_BINARY_DIR}/core/zco ${OBJECT_NAME}.zco
	      DEPENDS ${OBJECT_NAME}.zco
	      )
endmacro(parse_zco OBJECT_NAME)

parse_zco(z-set)
parse_zco(z-set-iter)
parse_zco(z-event-loop)
parse_zco(z-event-loop-linux)
parse_zco(z-event-loop-posix)
parse_zco(z-in-out-multiplexer)
parse_zco(z-worker-group)
parse_zco(z-framework-events)
parse_zco(z-guid)
parse_zco(z-application)
parse_zco(z-session-manager)
parse_zco(z-server)
parse_zco(z-stream)
parse_zco(z-net-stream)
parse_zco(z-socket)
parse_zco(z-log)
parse_zco(z-c-closure-marshal)
parse_zco(z-bind)
parse_zco(z-in-out)

add_library(
   zclib-extra SHARED
   zco-app-context.c
   z-set.c
   z-set-iter.c
   z-event-loop.c
   z-event-loop-linux.c
   z-event-loop-posix.c
   z-in-out-multiplexer.c
   z-worker-group.c
   z-framework-events.c
   z-guid.c
   z-application.c
   z-session-manager.c
   z-server.c
   z-stream.c
   z-net-stream.c
   z-socket.c
   z-log.c
   z-c-closure-marshal.c
   z-bind.c
   z-bind-util.c
   z-in-out.c
   )

