cmake_minimum_required(VERSION 2.8)
set(CMAKE_VERBOSE_MAKEFILE OFF)
project(net)

find_package(BISON)
find_package(FLEX)
include_directories(
      ${CMAKE_SOURCE_DIR}/core	       # core header files
      ${CMAKE_BINARY_DIR}/core	       # generated core header files
      ${CMAKE_SOURCE_DIR}/base	       # base header files
      ${CMAKE_BINARY_DIR}/base	       # generated base header files
      ${CMAKE_BINARY_DIR}/net	       # generated net header files
      )

macro(parse_zco OBJECT_NAME)
	add_custom_command(
	      OUTPUT ${OBJECT_NAME}.h ${OBJECT_NAME}.c
	      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/${OBJECT_NAME}.zco ${CMAKE_CURRENT_BINARY_DIR}/
	      COMMAND ${CMAKE_BINARY_DIR}/core/zco ${OBJECT_NAME}.zco
	      DEPENDS ${OBJECT_NAME}.zco
	      )
endmacro(parse_zco OBJECT_NAME)

parse_zco(z-server)
parse_zco(z-stream)
parse_zco(z-socket)

add_library(
   zclib-net SHARED
   z-server.c
   z-stream.c
   z-socket.c
   )

