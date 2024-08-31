project (tinyhash-lib)

set (TINYHASH_NAME "tinyhash" CACHE INTERNAL "")

if (BUILD_STATIC)
  set (TINYHASH_LIB_TYPE STATIC)
else ()
  set (TINYHASH_LIB_TYPE SHARED)
endif ()

add_subdirectory(common)
add_subdirectory(separate_chaining)

set (TINYHASH_SRC
  tinyhash.c
)

set (TINYHASH_HEADERS
  tinyhash.h
)

add_library(
  ${TINYHASH_NAME} ${TINYHASH_LIB_TYPE}
  ${TINYHASH_SRC}
  $<TARGET_OBJECTS:common_objects>
  $<TARGET_OBJECTS:separate_chaining_objects>
)
install (TARGETS ${TINYHASH_NAME} DESTINATION lib)

install (FILES ${TINYHASH_HEADERS} DESTINATION include/${TINYHASH_NAME})
