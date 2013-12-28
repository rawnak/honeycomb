cmake_minimum_required(VERSION 2.8)

add_definitions(-pipe -g -fstack-protector-all -O0 -std=gnu99)

add_subdirectory(bootstrap)
add_subdirectory(core)
add_subdirectory(base)
add_subdirectory(extra)
add_subdirectory(widgets)
add_subdirectory(apps)

