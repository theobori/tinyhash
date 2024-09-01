# C hashmap implementations

[![build](https://github.com/theobori/tinyhash/actions/workflows/build.yml/badge.svg)](https://github.com/theobori/tinyhash/actions/workflows/build.yml) [![lint](https://github.com/theobori/tinyhash/actions/workflows/lint.yml/badge.svg)](https://github.com/theobori/tinyhash/actions/workflows/lint.yml)

This is a library containing multiple C implementations of hashmap. The public API is deliberately simple and user-friendly.

Here are the different methods implemented:
- [Separate chaining](./src/separate_chaining/)
- [Open addressing](./src/open_addressing/)

## 📖 Build and run

For the build, you only need the following requirements:

- [CMake](https://cmake.org/download/) minimum 3.10

To build the library, you can run the following commands.
```sh
mkdir build
cd build
cmake ..
make
```

If you want to install the library, you can run the following command.
```sh
make install
```

The following CMake build arguments are available to enable or disable options.


| Name | Description | Default value |
| -- | -- | -- |
| `-DBUILD_TESTS` | Compile the test files | **`ON`**
| `-DBUILD_STATIC` | Link as a static library (instead of a shared library) | **`OFF`**

## 🤝 Contribute

If you want to help the project, you can follow the guidelines in [CONTRIBUTING.md](./CONTRIBUTING.md).

## 🧪 Tests

Make sure you run CMake with the `-DBUILD_TESTS=ON` flag.
The generated Makefile will contain a special `test` target, so you can run the tests with the following command:

```bash
make test
```

## 📎 Some examples

Here is a basic example of how you could use the hashmap.

### With the root controller (high level)
```c
#include "src/tinyhash.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <tinyhash/tinyhash.h>

typedef struct {
  char name[10];
  bool is_hydrated;
} Person;

int main(int argc, const char *argv[]) {
  bool success;
  Person person = {"James", true};

  // Create a controller with the separate chaining method
  th_t th = th_create(TH_OPEN_ADRESSING);

  // Insert a new key value pair
  success = th_put(&th, "key_1", strlen("key_1"), &person);
  if (success == false) {
    fprintf(stderr, "Unable to insert\n");
    return 1;
  }

  // Get the last inserted value
  Person *james;
  james = th_get(&th, "key_1", strlen("key_1"));
  if (success == false) {
    fprintf(stderr, "It does not exist\n");
    return 1;
  }

  printf("name -> %s, is_hydrated -> %d\n", james->name, james->is_hydrated);

  // Delete the entry
  success = th_delete(&th, "key_1", strlen("key_1"));
  if (success == false) {
    fprintf(stderr, "Unable to delete\n");
    return 1;
  }

  // Verify that it doesnt exist anymore
  james = th_get(&th, "key_1", strlen("key_1"));
  if (james != NULL) {
    fprintf(stderr, "The entry still exists\n");
    return 1;
  }

  // Free the allocated memory
  th_free(&th);

  return 0;
}
```

### Without the root controller (lower level)

This is exactly the same logic as using the root controller, although the prefix of functions and types will change.

For example, to use the ‘separate chaining’ method, the prefix will be `th_sc_table`.

```c
#include <string.h>

#include <tinyhash/separate_chaining/table.h>

int main(int argc, const char *argv[]) {
  th_sc_table_t table;

  th_sc_table_init(&table);
  th_sc_table_put(&table, "hello", strlen("hello"), (th_any_t)0);
  // etc..

  return 0;
}
```
