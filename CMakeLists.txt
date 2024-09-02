cmake_minimum_required(VERSION 3.10)

project(tinyhash VERSION 0.0.1 LANGUAGES C DESCRIPTION "This is a library containing multiple C implementations of hashmap.")

option(BUILD_TESTS "Build the tests" OFF)
option(BUILD_DOC "Build the documentation" OFF)

add_subdirectory(src)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif ()

if (BUILD_DOC)
    add_subdirectory(doc)
endif ()