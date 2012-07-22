cmake_minimum_required(VERSION 2.8)
set(CMAKE_VERBOSE_MAKEFILE OFF)
project(zco)
find_package(BISON)
find_package(FLEX)
include_directories(
      ${CMAKE_CURRENT_SOURCE_DIR}/core       # core header files
      ${CMAKE_CURRENT_BINARY_DIR}            # generated header files
      ${CMAKE_CURRENT_SOURCE_DIR}/bootstrap  # pre-generated header files for bootstrapping
      /usr/lib/libffi-3.0.11/include         # libffi
      )

# zco compiler
add_definitions(-pipe -g -fstack-protector-all -O0 -std=gnu99)

bison_target(ZCO_PARSER core/zco.y ${CMAKE_CURRENT_BINARY_DIR}/zco.tab.c)
flex_target(ZCO_SCANNER core/zco.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)
add_flex_bison_dependency(ZCO_SCANNER ZCO_PARSER)

# bootstrapped zco compiler
add_executable(
      bootstrap
      EXCLUDE_FROM_ALL
      ${BISON_ZCO_PARSER_OUTPUTS}
      ${FLEX_ZCO_SCANNER_OUTPUTS}
      core/zco-type.c
      bootstrap/z-closure.c
      bootstrap/z-closure-marshal.c
      bootstrap/z-map.c
      bootstrap/z-map-iter.c
      bootstrap/z-string.c
      bootstrap/z-string-iter.c
      bootstrap/z-vector.c
      bootstrap/z-vector-iter.c
      bootstrap/z-object.c
      bootstrap/z-file.c
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

target_link_libraries(zco m zclib ffi)

# test driver
add_executable(
   zco-test
   z-test-object.c
   core/signal-test.c
   core/zco-test.c
   core/z-vector-test.c
   core/z-string-test.c
   core/z-map-test.c
   )

target_link_libraries(zco-test zclib m ffi)

# FastCGI application
add_executable(
   zco-gateway
   z-gateway-application.c
   )

target_link_libraries(zco-gateway zclib m ffi fcgi)

# zclib
add_custom_command(
      OUTPUT z-object.h z-object.c
      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/core/z-object.zco ${CMAKE_CURRENT_BINARY_DIR}/
      COMMAND ./zco z-object.zco
      DEPENDS core/z-object.zco
      )

add_custom_command(
      OUTPUT z-vector-iter.h z-vector-iter.c
      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/core/z-vector-iter.zco ${CMAKE_CURRENT_BINARY_DIR}/
      COMMAND ./zco z-vector-iter.zco
      DEPENDS core/z-vector-iter.zco
      )

add_custom_command(
      OUTPUT z-vector.h z-vector.c
      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/core/z-vector.zco ${CMAKE_CURRENT_BINARY_DIR}/
      COMMAND ./zco z-vector.zco
      DEPENDS core/z-vector.zco
      )
add_custom_command(
      OUTPUT z-string-iter.h z-string-iter.c
      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/core/z-string-iter.zco ${CMAKE_CURRENT_BINARY_DIR}/
      COMMAND ./zco z-string-iter.zco
      DEPENDS core/z-string-iter.zco
      )

add_custom_command(
      OUTPUT z-string.h z-string.c
      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/core/z-string.zco ${CMAKE_CURRENT_BINARY_DIR}/
      COMMAND ./zco z-string.zco
      DEPENDS core/z-string.zco
      )

add_custom_command(
      OUTPUT z-map-iter.h z-map-iter.c
      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/core/z-map-iter.zco ${CMAKE_CURRENT_BINARY_DIR}/
      COMMAND ./zco z-map-iter.zco
      DEPENDS core/z-map-iter.zco
      )

add_custom_command(
      OUTPUT z-map.h z-map.c
      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/core/z-map.zco ${CMAKE_CURRENT_BINARY_DIR}/
      COMMAND ./zco z-map.zco
      DEPENDS core/z-map.zco
      )

add_custom_command(
      OUTPUT z-log.h z-log.c
      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/core/z-log.zco ${CMAKE_CURRENT_BINARY_DIR}/
      COMMAND ./zco z-log.zco
      DEPENDS core/z-log.zco
      )

add_custom_command(
      OUTPUT z-value.h z-value.c
      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/core/z-value.zco ${CMAKE_CURRENT_BINARY_DIR}/
      COMMAND ./zco z-value.zco
      DEPENDS core/z-value.zco
      )

add_custom_command(
      OUTPUT z-closure.h z-closure.c
      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/core/z-closure.zco ${CMAKE_CURRENT_BINARY_DIR}/
      COMMAND ./zco z-closure.zco
      DEPENDS core/z-closure.zco
      )

add_custom_command(
      OUTPUT z-closure-marshal.h z-closure-marshal.c
      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/core/z-closure-marshal.zco ${CMAKE_CURRENT_BINARY_DIR}/
      COMMAND ./zco z-closure-marshal.zco
      DEPENDS core/z-closure-marshal.zco
      )

add_custom_command(
      OUTPUT z-c-closure-marshal.h z-c-closure-marshal.c
      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/core/z-c-closure-marshal.zco ${CMAKE_CURRENT_BINARY_DIR}/
      COMMAND ./zco z-c-closure-marshal.zco
      DEPENDS core/z-c-closure-marshal.zco
      )

add_custom_command(
      OUTPUT z-test-object.h z-test-object.c
      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/core/z-test-object.zco ${CMAKE_CURRENT_BINARY_DIR}/
      COMMAND ./zco z-test-object.zco
      DEPENDS core/z-test-object.zco
      )

add_custom_command(
      OUTPUT z-file.h z-file.c
      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/core/z-file.zco ${CMAKE_CURRENT_BINARY_DIR}/
      COMMAND ./zco z-file.zco
      DEPENDS core/z-file.zco
      )

add_custom_command(
      OUTPUT z-gateway-application.h z-gateway-application.c
      COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/apps/gateway/z-gateway-application.zco ${CMAKE_CURRENT_BINARY_DIR}/
      COMMAND ./zco z-gateway-application.zco
      DEPENDS apps/gateway/z-gateway-application.zco
      )

add_library(zclib SHARED
      core/zco-type.c
      z-object.c
      z-vector-iter.c
      z-vector.c
      z-string-iter.c
      z-string.c
      z-map-iter.c
      z-map.c
      z-log.c
      z-value.c
      z-closure.c
      z-closure-marshal.c
      z-c-closure-marshal.c
      z-file.c
      )

