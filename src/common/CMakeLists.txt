set(COMMON_SRC
    hash.c
    key.c
)

set(COMMON_HEADERS
    hash.h
    key.h
    types.h
)

add_library(common_objects OBJECT ${COMMON_SRC})

install(
  FILES ${COMMON_HEADERS}
  DESTINATION include/${TINYHASH_NAME}/common
)
