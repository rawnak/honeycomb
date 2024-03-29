cmake_minimum_required(VERSION 2.8)
set(CMAKE_VERBOSE_MAKEFILE OFF)
project(bootstrap)
find_package(BISON)
find_package(FLEX)
include_directories(
      ${CMAKE_SOURCE_DIR}/core               # core header files
      ${CMAKE_CURRENT_SOURCE_DIR}            # pre-generated header files for bootstrapping
      )

bison_target(ZCO_PARSER ${CMAKE_SOURCE_DIR}/core/zco.y ${CMAKE_CURRENT_BINARY_DIR}/zco.tab.c)
flex_target(ZCO_SCANNER ${CMAKE_SOURCE_DIR}/core/zco.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)
add_flex_bison_dependency(ZCO_SCANNER ZCO_PARSER)

add_definitions(-DBOOTSTRAP)

# bootstrapped zco compiler
add_executable(
      bootstrap
      EXCLUDE_FROM_ALL
      ${BISON_ZCO_PARSER_OUTPUTS}
      ${FLEX_ZCO_SCANNER_OUTPUTS}
      ${CMAKE_SOURCE_DIR}/core/zco-context.c
      z-zco-source-generator.c
      z-map.c
      z-map-iter.c
      z-string.c
      z-string-iter.c
      z-vector.c
      z-vector-iter.c
      z-vector-segment.c
      z-object.c
      z-file.c
      z-object-tracker.c
      z-memory-allocator.c
      z-sys-memory-allocator.c
)

target_link_libraries(bootstrap m pthread)
set_target_properties(bootstrap
      PROPERTIES OUTPUT_NAME zco)

