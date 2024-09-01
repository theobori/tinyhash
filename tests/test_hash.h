#ifndef __TINYHASH_TEST_HASH_H__
#define __TINYHASH_TEST_HASH_H__

#include "munit/munit.h"

MunitResult test_th_hash(const MunitParameter params[], void *data);
MunitResult test_th_hash_multiple_iteration(const MunitParameter params[],
                                            void *data);
MunitResult test_th_hash_null(const MunitParameter params[], void *data);
MunitResult test_th_hash_with_int(const MunitParameter params[], void *data);

#endif
