cmake_minimum_required(VERSION 2.8)
set(CMAKE_VERBOSE_MAKEFILE OFF)
project(gateway)

find_package(BISON)
find_package(FLEX)
include_directories(
      ${CMAKE_SOURCE_DIR}/core	       # core header files
      ${CMAKE_BINARY_DIR}/core	       # generated core header files
      ${CMAKE_CURRENT_BINARY_DIR}      # generated widget header files
      )

add_definitions(-pipe -g -fstack-protector-all -O0 -std=gnu99)

macro(parse_zco OBJECT_NAME)
	add_custom_command(
	      OUTPUT ${OBJECT_NAME}.h ${OBJECT_NAME}.c
	      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/${OBJECT_NAME}.zco ${CMAKE_CURRENT_BINARY_DIR}/
	      COMMAND ${CMAKE_BINARY_DIR}/core/zco ${OBJECT_NAME}.zco
	      DEPENDS ${OBJECT_NAME}.zco
	      )
endmacro(parse_zco OBJECT_NAME)

parse_zco(z-window)

add_library(
   zclib-widgets SHARED
   z-window.c
   )

