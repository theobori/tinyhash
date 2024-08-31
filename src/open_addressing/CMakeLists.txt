set(OPEN_ADDRESSING_SRC
    table.c
)

set(OPEN_ADDRESSING_HEADERS
    entry.h
    table.h
)

add_library(open_addressing_objects OBJECT ${OPEN_ADDRESSING_SRC})

install(
  FILES ${OPEN_ADDRESSING_HEADERS}
  DESTINATION include/${TINYHASH_NAME}/open_addressing
)
