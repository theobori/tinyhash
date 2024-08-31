set(SEPARATE_CHAINING_SRC
    entry.c
    table.c
)

set(SEPARATE_CHAINING_HEADERS
    entry.h
    table.h
)

add_library(separate_chaining_objects OBJECT ${SEPARATE_CHAINING_SRC})

install(
  FILES ${SEPARATE_CHAINING_HEADERS}
  DESTINATION include/${TINYHASH_NAME}/separate_chaining
)
