cmake_minimum_required(VERSION 2.8)
set(CMAKE_VERBOSE_MAKEFILE OFF)
project(core-test)

find_package(BISON)
find_package(FLEX)
include_directories(
      ${CMAKE_SOURCE_DIR}/core	       # core header files
      ${CMAKE_BINARY_DIR}/core	       # generated core header files
      ${CMAKE_SOURCE_DIR}/base	       # base header files
      ${CMAKE_BINARY_DIR}/base         # generated base header files
      ${CMAKE_BINARY_DIR}/net          # generated net header files
      ${CMAKE_BINARY_DIR}/extra        # generated extra header files
      ${CMAKE_CURRENT_SOURCE_DIR}      # application header files
      ${CMAKE_CURRENT_BINARY_DIR}      # generated application header files
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

parse_zco(z-test-object)
parse_zco(z-test-derived-object)

# test driver
add_executable(
   core-test
   z-test-object.c
   z-test-derived-object.c
   signal-test.c
   network-test.c
   main.c
   z-vector-test.c
   z-string-test.c
   z-map-test.c
   z-set-test.c
   )

target_link_libraries(core-test zclib-core zclib-base zclib-net zclib-extra m ffi pthread)


