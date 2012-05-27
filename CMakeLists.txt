cmake_minimum_required(VERSION 2.8)
set(CMAKE_VERBOSE_MAKEFILE OFF)
find_package(BISON)
find_package(FLEX)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# zco compiler
project(zco)
add_definitions(-pipe -g -fstack-protector-all)

bison_target(ZCO_PARSER zco.y ${CMAKE_CURRENT_BINARY_DIR}/zco.tab.c)
flex_target(ZCO_SCANNER zco.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)
add_flex_bison_dependency(ZCO_SCANNER ZCO_PARSER)

# zco compiler
add_executable(
      zco
      ${BISON_ZCO_PARSER_OUTPUTS}
      ${FLEX_ZCO_SCANNER_OUTPUTS}
      zco-type.c
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

target_link_libraries(zco-test zclib)

# zclib
add_definitions(-pipe -g -fstack-protector-all)

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
      )
      
