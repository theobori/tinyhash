include_directories("../src")

project (tinyhash-tests)

set (TINYHASH_SRC_TESTS
  munit/munit.c
  tests.c
  test_hash.c
  test_table.c
)

add_executable (tests ${TINYHASH_SRC_TESTS})
target_link_libraries (tests ${TINYHASH_NAME})

add_custom_target(test COMMAND tests)
