cmake_minimum_required(VERSION 2.8)
set(CMAKE_VERBOSE_MAKEFILE OFF)
project(base)

find_package(BISON)
find_package(FLEX)
include_directories(
      ${CMAKE_SOURCE_DIR}/core	       # core header files
      ${CMAKE_BINARY_DIR}/core	       # generated core header files
      ${CMAKE_SOURCE_DIR}/base	       # base header files
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

parse_zco(z-event-loop)
parse_zco(z-event-loop-linux)
parse_zco(z-event-loop-posix)
parse_zco(z-in-out-multiplexer)
parse_zco(z-c-closure-marshal)
parse_zco(z-bind)
parse_zco(z-in-out)

add_library(
   zclib-base SHARED
   zco-app-context.c
   z-event-loop.c
   z-event-loop-linux.c
   z-event-loop-posix.c
   z-in-out-multiplexer.c
   z-c-closure-marshal.c
   z-bind.c
   z-bind-util.c
   z-in-out.c
   )

