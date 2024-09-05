set(COMMON_SRC
    hash.c
    key.c
    iterator.c
)

set(COMMON_HEADERS
    hash.h
    key.h
    types.h
    table.h
    iterator.h
)

add_library(common_objects OBJECT ${COMMON_SRC})

install(
  FILES ${COMMON_HEADERS}
  DESTINATION include/${TINYHASH_NAME}/common
)
