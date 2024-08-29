#include "munit/munit.h"

#include "../src/table.h"
#include <stdint.h>
#include <string.h>

typedef struct {
    uint32_t a;
    uint8_t b[22];
} TestStruct;

#define SET_GET_ITERATIONS 256 * 256


MunitResult test_th_table_put_and_get(const MunitParameter params[], void* data)
{
    th_table_t table;
    th_any_t *value;

    th_table_init(&table);

    th_table_put(&table, "hello", strlen("hello"), (void *) 333);
    value = th_table_get(&table, "hello", strlen("hello"));

    munit_assert_uint64((uint64_t) value, ==, 333);

    th_table_destroy(&table);

    return MUNIT_OK;
}

MunitResult test_th_table_get_with_empty_table(const MunitParameter params[], void* data)
{
    th_table_t table;
    th_any_t value;

    th_table_init(&table);

    value = th_table_get(&table, "hello", strlen("hello"));

    th_table_destroy(&table);

    return MUNIT_OK;
}

MunitResult test_th_table_put_with_full_table(const MunitParameter params[], void* data)
{
    th_table_t table;
    int *value;

    th_table_init(&table);

    for (int i = 0; i < SET_GET_ITERATIONS; i++) {
        int *j = malloc(sizeof(i));
        *j = i;

        th_table_put(&table, j, sizeof(i), j);
    }


    for (int i = 0; i < SET_GET_ITERATIONS; i++) {
        value = (int *) th_table_get(&table, &i, sizeof(i));

        munit_assert_int(*value, ==, i);

        free(value);
    }

    th_table_put(&table, "b", strlen("b"), (void *) 1);
    th_table_put(&table, "c", strlen("c"), (void *) 1);
    th_table_put(&table, "d", strlen("d"), (void *) 1);
    th_table_put(&table, "e", strlen("e"), (void *) 1);
    th_table_put(&table, "f", strlen("f"), (void *) 1);
    th_table_put(&table, "g", strlen("g"), (void *) 1);
    th_table_put(&table, "h", strlen("h"), (void *) 1);


    th_table_put(&table, "azdaz", strlen("azdaz"), (void *) 10);

    value = th_table_get(&table, "azdaz", strlen("azdaz"));

    munit_assert_int((uint64_t) value, ==, 10);

    th_table_destroy(&table);

    return MUNIT_OK;
}

MunitResult test_th_table_put_overwrite(const MunitParameter params[], void* data)
{
    th_table_t table;
    th_any_t value;

    th_table_init(&table);

    th_table_put(&table, "a", strlen("a"), (void *) 1);
    th_table_put(&table, "b", strlen("b"), (void *) 1);
    th_table_put(&table, "a", strlen("a"), (void *) 2);

    value = th_table_get(&table, "a", strlen("a"));

    munit_assert_uint64((uint64_t) value, ==, 2);

    th_table_destroy(&table);

    return MUNIT_OK;
}

MunitResult test_th_table_put_collision(const MunitParameter params[], void* data)
{
    th_table_t table;
    th_any_t value;

    th_table_init(&table);

    th_table_put(&table, "b", strlen("b"), (void *) 123);
    th_table_put(&table, "ello", strlen("ello"), (void *) 456);
    
    value = th_table_get(&table, "b", strlen("b"));
    munit_assert_uint64((uint64_t) value, ==, 123);

    value = th_table_get(&table, "ello", strlen("ello"));
    munit_assert_uint64((uint64_t) value, ==, 456);

    th_table_destroy(&table);

    return MUNIT_OK;
}

MunitResult test_th_table_put_struct_as_key(const MunitParameter params[], void* data)
{
    th_table_t table;
    th_any_t value;
    TestStruct test_struct;

    memset(&test_struct, 0, sizeof(TestStruct));

    test_struct.b[3] = 222;

    th_table_init(&table);

    th_table_put(&table, &test_struct, sizeof(TestStruct), (void *) 123);
    
    value = th_table_get(&table, &test_struct, sizeof(TestStruct));
    munit_assert_uint64((uint64_t) value, ==, 123);

    munit_assert_uint8(test_struct.b[3], ==, 222);

    th_table_destroy(&table);

    return MUNIT_OK;
}
