
#include "munit/munit.h"

#include "../src/hash.h"
#include <stdint.h>
#include <stdio.h>

static struct { char *str; uint32_t hash;} values[] = {
    {"hello", 1335831723 },
    {"world", 933488787 },
    {"14738", 672216534 },
    {"18013", 4041707876 },
    {"28502", 1698934288 },
    {"27", 2331153606 },
    {"22125", 3038097389 },
    {"13228", 617068255 },
    {"7269", 398476757 },
    {"32576", 342715562 },
    {"29098", 4228780613 },
    {"6986", 2934559306 },
    {"5484", 3905864472 },
    {"", 2166136261 },
};

MunitResult test_th_hash(const MunitParameter params[], void* data)
{
    (void) params;
    (void) data;

    for (int i = 0; i < 14; i++) {
        uint32_t hash = th_hash((uint8_t *) values[i].str, strlen(values[i].str));

        munit_assert_uint(hash, ==, values[i].hash);
    }

    return MUNIT_OK;
}

MunitResult test_th_hash_multiple_iteration(const MunitParameter params[], void* data)
{
    (void) params;
    (void) data;

    for (int i = 0; i < 5; i++) {
        uint32_t hash = th_hash((uint8_t *) values[0].str, strlen(values[i].str));

        munit_assert_uint(hash, ==, values[0].hash);
    }

    return MUNIT_OK;
}

MunitResult test_th_hash_null(const MunitParameter params[], void* data)
{
    (void) params;
    (void) data;

    uint32_t hash = th_hash(NULL, 0);

    munit_assert_uint(hash, ==, 0);

    return MUNIT_OK;
}

MunitResult test_th_hash_with_int(const MunitParameter params[], void* data)
{
    (void) params;
    (void) data;

    int a = 123;

    uint32_t hash = th_hash((uint8_t *) &a, 4);

    munit_assert_uint(hash, ==, 442514334);

    return MUNIT_OK;
}
