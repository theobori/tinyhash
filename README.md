# C hashmap implementations

[![build](https://github.com/theobori/tinyhash/actions/workflows/build.yml/badge.svg)](https://github.com/theobori/tinyhash/actions/workflows/build.yml) [![lint](https://github.com/theobori/tinyhash/actions/workflows/lint.yml/badge.svg)](https://github.com/theobori/tinyhash/actions/workflows/lint.yml)

[![built with nix](https://builtwithnix.org/badge.svg)](https://builtwithnix.org)

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
| `-DBUILD_DOC` | Build the documentation | **`OFF`**

## 🤝 Contribute

If you want to help the project, you can follow the guidelines in [CONTRIBUTING.md](./CONTRIBUTING.md).

## 🧪 Tests

Make sure you run CMake with the `-DBUILD_TESTS=ON` flag.
The generated Makefile will contain a special `test` target, so you can run the tests with the following command:

```bash
make test
```

## 📝 Documentation

Just make sure you run CMake with the `-DBUILD_DOC=ON` flag.

The Makefile `all` target will automatically build the documentation.

## 📎 Some examples

Here is a basic example of how you could use the hashmap.

### With the root controller (high level)

```c
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <tinyhash/tinyhash.h>

typedef struct {
  char name[10];
  bool is_hydrated;
} person_t;

int main(int argc, const char *argv[]) {
  bool success;
  person_t person = {"James", true};

  // Create a controller with the open addressing method
  th_t th = th_create(TH_OPEN_ADRESSING);

  // Insert a new key value pair
  success = th_put(&th, "key_1", strlen("key_1"), &person);
  if (success == false) {
    fprintf(stderr, "Unable to insert\n");
    return 1;
  }

  // Get the last inserted value
  person_t *james;
  james = th_get(&th, "key_1", strlen("key_1"));
  if (success == false) {
    fprintf(stderr, "It does not exist\n");
    return 1;
  }

  printf("name -> %s, is_hydrated -> %d, hashmap length -> %d\n", james->name,
         james->is_hydrated, th_len(&th));

  // Quick multiple insert with the same value (not important here)
  th_put(&th, "key_2", strlen("key_2"), &person);
  th_put(&th, "key_3", strlen("key_3"), &person);
  th_put(&th, "key_4", strlen("key_4"), &person);

  printf("hashmap length -> %d\n", th_len(&th));

  th_iterator_t *it;
  person_t *p;

  // Iterate with a for loop
  for (it = th_begin_iterator(&th); it != NULL; th_iterator_next(&it)) {
    p = it->value;
    printf("[for] key -> %s, name -> %s\n", it->key->data, p->name);
  }

  // Iterate with a while loop
  it = th_empty_iterator(&th);
  while (th_iterator_next(&it) == true) {
    p = it->value;
    printf("[while] key -> %s, name -> %s\n", it->key->data, p->name);
  }

  // Delete an entry
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

For example, to use the ‘separate chaining’ method, the prefix will be `th_sc_table`.f

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
