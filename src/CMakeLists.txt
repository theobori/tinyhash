project (tinyhash-lib)

set (TINYHASH_NAME "tinyhash" CACHE INTERNAL "")

if (BUILD_STATIC)
  set (TINYHASH_LIB_TYPE STATIC)
else ()
  set (TINYHASH_LIB_TYPE SHARED)
endif ()

set (
    TINYHASH_SRC
    hash.c
    entry.c
    table.c
)

set (
    TINYHASH_HEADERS
    entry.h
    table.h
    hash.h
    options.h
)

add_library (${TINYHASH_NAME} ${TINYHASH_LIB_TYPE} ${TINYHASH_SRC})

install (TARGETS ${TINYHASH_NAME} DESTINATION lib)
install (FILES ${TINYHASH_HEADERS} DESTINATION include/${TINYHASH_NAME})
