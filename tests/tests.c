#include "munit/munit.h"

#include "test_hash.h"
#include "test_table.h"

static MunitTest test_th_suite_tests[] = {
    {
        "/th_hash_str",
        test_th_hash,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/th_hash_str_multiple_iteration",
        test_th_hash_multiple_iteration,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/th_hash_str_null",
        test_th_hash_null,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/th_hash_str_with_int",
        test_th_hash_with_int,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/th_table_set_and_get",
        test_th_table_put_and_get,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/th_table_get_with_empty_table",
        test_th_table_get_with_empty_table,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/th_table_set_with_full_table",
        test_th_table_put_with_full_table,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/th_table_set_overwrite",
        test_th_table_put_overwrite,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/th_table_set_collision",
        test_th_table_put_collision,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/th_table_put_struct_as_key",
        test_th_table_put_struct_as_key,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/th_table_delete",
        test_th_table_delete,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_th_suite = {
    "tinyhash",
    test_th_suite_tests,
    NULL,
    0,

    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
    return munit_suite_main(
        &test_th_suite,
        (void*) "", argc, argv
    );
}
