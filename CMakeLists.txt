cmake_minimum_required(VERSION 3.10)

project(tinyhash VERSION 0.0.1 LANGUAGES C DESCRIPTION "Simple C hash table implementation.")

add_subdirectory(src)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif ()
