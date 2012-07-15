cmake_minimum_required(VERSION 2.8)
set(CMAKE_VERBOSE_MAKEFILE OFF)
project(zco)
find_package(BISON)
find_package(FLEX)
include_directories(
      ${CMAKE_CURRENT_SOURCE_DIR}            # core header files
      ${CMAKE_CURRENT_BINARY_DIR}            # generated header files
      ${CMAKE_CURRENT_SOURCE_DIR}/bootstrap  # pre-generated header files for bootstrapping
      )

# zco compiler
add_definitions(-pipe -g -fstack-protector-all)

bison_target(ZCO_PARSER zco.y ${CMAKE_CURRENT_BINARY_DIR}/zco.tab.c)
flex_target(ZCO_SCANNER zco.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)
add_flex_bison_dependency(ZCO_SCANNER ZCO_PARSER)

# bootstrapped zco compiler
add_executable(
      bootstrap
      EXCLUDE_FROM_ALL
      ${BISON_ZCO_PARSER_OUTPUTS}
      ${FLEX_ZCO_SCANNER_OUTPUTS}
      zco-type.c
      bootstrap/z-map.c
      bootstrap/z-map-iter.c
      bootstrap/z-string.c
      bootstrap/z-string-iter.c
      bootstrap/z-vector.c
      bootstrap/z-vector-iter.c
      bootstrap/z-object.c
)

target_link_libraries(bootstrap m)
set_target_properties(bootstrap
      PROPERTIES OUTPUT_NAME zco)

# zco compiler
add_executable(
      zco
      ${BISON_ZCO_PARSER_OUTPUTS}
      ${FLEX_ZCO_SCANNER_OUTPUTS}
)

target_link_libraries(zco m zclib)

# test driver
add_executable(
   zco-test
   zco-test.c
   z-vector-test.c
   z-string-test.c
   z-map-test.c
   )

target_link_libraries(zco-test zclib m)

# zclib
add_custom_command(
      OUTPUT z-object.h z-object.c
      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/z-object.zco ${CMAKE_CURRENT_BINARY_DIR}/
      COMMAND ./zco z-object.zco
      DEPENDS z-object.zco
      )

add_custom_command(
      OUTPUT z-vector-iter.h z-vector-iter.c
      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/z-vector-iter.zco ${CMAKE_CURRENT_BINARY_DIR}/
      COMMAND ./zco z-vector-iter.zco
      DEPENDS z-vector-iter.zco
      )

add_custom_command(
      OUTPUT z-vector.h z-vector.c
      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/z-vector.zco ${CMAKE_CURRENT_BINARY_DIR}/
      COMMAND ./zco z-vector.zco
      DEPENDS z-vector.zco
      )
add_custom_command(
      OUTPUT z-string-iter.h z-string-iter.c
      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/z-string-iter.zco ${CMAKE_CURRENT_BINARY_DIR}/
      COMMAND ./zco z-string-iter.zco
      DEPENDS z-string-iter.zco
      )

add_custom_command(
      OUTPUT z-string.h z-string.c
      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/z-string.zco ${CMAKE_CURRENT_BINARY_DIR}/
      COMMAND ./zco z-string.zco
      DEPENDS z-string.zco
      )

add_custom_command(
      OUTPUT z-map-iter.h z-map-iter.c
      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/z-map-iter.zco ${CMAKE_CURRENT_BINARY_DIR}/
      COMMAND ./zco z-map-iter.zco
      DEPENDS z-map-iter.zco
      )

add_custom_command(
      OUTPUT z-map.h z-map.c
      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/z-map.zco ${CMAKE_CURRENT_BINARY_DIR}/
      COMMAND ./zco z-map.zco
      DEPENDS z-map.zco
      )

add_custom_command(
      OUTPUT z-log.h z-log.c
      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/z-log.zco ${CMAKE_CURRENT_BINARY_DIR}/
      COMMAND ./zco z-log.zco
      DEPENDS z-log.zco
      )

add_custom_command(
      OUTPUT z-value.h z-value.c
      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/z-value.zco ${CMAKE_CURRENT_BINARY_DIR}/
      COMMAND ./zco z-value.zco
      DEPENDS z-value.zco
      )

add_library(zclib SHARED
      zco-type.c
      z-object.c
      z-vector-iter.c
      z-vector.c
      z-string-iter.c
      z-string.c
      z-map-iter.c
      z-map.c
      z-log.c
      z-value.c
      )

