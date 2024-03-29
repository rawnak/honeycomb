cmake_minimum_required(VERSION 2.8)
set(CMAKE_VERBOSE_MAKEFILE OFF)
project(zco)

find_package(BISON)
find_package(FLEX)
include_directories(
      ${CMAKE_CURRENT_SOURCE_DIR}            # core header files
      ${CMAKE_CURRENT_BINARY_DIR}            # generated core header files
      /usr/lib/libffi-3.0.13/include         # libffi
      )

bison_target(ZCO_PARSER zco.y ${CMAKE_CURRENT_BINARY_DIR}/zco.tab.c)
flex_target(ZCO_SCANNER zco.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)
add_flex_bison_dependency(ZCO_SCANNER ZCO_PARSER)

if (EXISTS ${CMAKE_CURRENT_BINARY_DIR}/zco)
	macro(parse_zco OBJECT_NAME)
		add_custom_command(
		      OUTPUT ${OBJECT_NAME}.h ${OBJECT_NAME}.c
		      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/${OBJECT_NAME}.zco ${CMAKE_CURRENT_BINARY_DIR}/
		      COMMAND ${CMAKE_CURRENT_BINARY_DIR}/zco ${OBJECT_NAME}.zco
		      DEPENDS ${OBJECT_NAME}.zco
		      )
	endmacro(parse_zco OBJECT_NAME)

else (EXISTS ${CMAKE_CURRENT_BINARY_DIR}/zco)
	macro(parse_zco OBJECT_NAME)
		add_custom_command(
		      OUTPUT ${OBJECT_NAME}.h ${OBJECT_NAME}.c
		      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/${OBJECT_NAME}.zco ${CMAKE_CURRENT_BINARY_DIR}/
		      COMMAND ${CMAKE_BINARY_DIR}/bootstrap/zco ${OBJECT_NAME}.zco
		      DEPENDS ${OBJECT_NAME}.zco
		      )
	endmacro(parse_zco OBJECT_NAME)

endif (EXISTS ${CMAKE_CURRENT_BINARY_DIR}/zco)



# zco compiler
parse_zco(z-zco-source-generator)
add_executable(
      zco
      ${BISON_ZCO_PARSER_OUTPUTS}
      ${FLEX_ZCO_SCANNER_OUTPUTS}
      z-zco-source-generator.c
)

target_link_libraries(zco m zclib-core ffi pthread)

# zclib
parse_zco(z-object)
parse_zco(z-vector-iter)
parse_zco(z-vector-segment)
parse_zco(z-vector)
parse_zco(z-string-iter)
parse_zco(z-string)
parse_zco(z-map-iter)
parse_zco(z-map)
parse_zco(z-value)
parse_zco(z-closure)
parse_zco(z-closure-marshal)
parse_zco(z-file)
parse_zco(z-object-tracker)
parse_zco(z-default-object-tracker)
parse_zco(z-memory-allocator)
parse_zco(z-sys-memory-allocator)
parse_zco(z-simple-memory-allocator)
parse_zco(z-buddy-memory-allocator)
parse_zco(z-thread-simple-memory-allocator)

add_library(
      zclib-core SHARED
      zco-context.c
      z-object.c
      z-vector-iter.c
      z-vector-segment.c
      z-vector.c
      z-string-iter.c
      z-string.c
      z-map-iter.c
      z-map.c
      z-value.c
      z-closure.c
      z-closure-marshal.c
      z-file.c
      z-object-tracker.c
      z-memory-allocator.c
      z-sys-memory-allocator.c
      z-simple-memory-allocator.c
      z-buddy-memory-allocator.c
      z-thread-simple-memory-allocator.c
      z-default-object-tracker.c
      )

