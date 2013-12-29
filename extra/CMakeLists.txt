cmake_minimum_required(VERSION 2.8)
set(CMAKE_VERBOSE_MAKEFILE OFF)
project(extra)

find_package(BISON)
find_package(FLEX)
include_directories(
      ${CMAKE_SOURCE_DIR}/core	       # core header files
      ${CMAKE_BINARY_DIR}/core	       # generated core header files
      ${CMAKE_SOURCE_DIR}/base	       # base header files
      ${CMAKE_BINARY_DIR}/base	       # generated base header files
      ${CMAKE_BINARY_DIR}/net	       # generated net header files
      ${CMAKE_SOURCE_DIR}/extra	       # extra header files
      ${CMAKE_CURRENT_BINARY_DIR}      # generated extra header files
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
parse_zco(z-worker-group)
parse_zco(z-framework-events)
parse_zco(z-guid)
parse_zco(z-application)
parse_zco(z-session-manager)
parse_zco(z-log)

add_library(
   zclib-extra SHARED
   z-set.c
   z-set-iter.c
   z-worker-group.c
   z-framework-events.c
   z-guid.c
   z-application.c
   z-session-manager.c
   z-log.c
   )

