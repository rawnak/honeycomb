cmake_minimum_required(VERSION 2.8)
set(CMAKE_VERBOSE_MAKEFILE OFF)
project(bootstrap)
find_package(BISON)
find_package(FLEX)
include_directories(
      ${CMAKE_SOURCE_DIR}/core               # core header files
      ${CMAKE_CURRENT_SOURCE_DIR}            # pre-generated header files for bootstrapping
      )

add_definitions(-pipe -g -fstack-protector-all -O0 -std=gnu99)

bison_target(ZCO_PARSER ${CMAKE_SOURCE_DIR}/core/zco.y ${CMAKE_CURRENT_BINARY_DIR}/zco.tab.c)
flex_target(ZCO_SCANNER ${CMAKE_SOURCE_DIR}/core/zco.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)
add_flex_bison_dependency(ZCO_SCANNER ZCO_PARSER)

# bootstrapped zco compiler
add_executable(
      bootstrap
      ${BISON_ZCO_PARSER_OUTPUTS}
      ${FLEX_ZCO_SCANNER_OUTPUTS}
      ${CMAKE_SOURCE_DIR}/core/zco-type.c
      z-closure.c
      z-closure-marshal.c
      z-map.c
      z-map-iter.c
      z-string.c
      z-string-iter.c
      z-vector.c
      z-vector-iter.c
      z-object.c
      z-file.c
)

target_link_libraries(bootstrap m)
set_target_properties(bootstrap
      PROPERTIES OUTPUT_NAME zco)

