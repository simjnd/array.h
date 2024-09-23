# array.h
### Single-header small array implementation
---

Inspired by [Simple Dynamic Strings](https://github.com/antirez/sds), this is a
simple single-header library that provides metadata augmented heap-allocated
arrays in C.

When you heap-allocate an array with this library, it also reserves a 32-bit
header that stores the length of the array you allocated. This simplifies array
manipulation and bounds-checking with good performance by colocating this
information and thus providing good cache locality.

This is all made transparent to the user as the pointer they receive is at the
data portion of the array so you can read and assign to it as with a traditional
array.

```
+--------+--------------------+
| Length | Array content      |
+--------+--------------------+
         |
         `-> Pointer returned to the user.
```

Portability has been considered by providing a macro that abstracts dynamic
allocation and de-allocation. The user can replace the default value by whatever
mechanism he chooses to perform memory allocations. The macros are `_arr_alloc` 
and `_arr_dealloc`, which default to `malloc` and `free`.


# Usage
---

Include the header file in every file you want to use it.
```c
#include "array.h"
```

In **ONE** file, define `ARRAY_IMPL` **before** including the header file.
```c
#define ARRAY_IMPL
#include "array.h"
```

# Documentation
---

**arr_new**
```c
array_t arr_new(int n, size_t size);
```
Allocates a new array on the heap, of size `n * size`.

*Example*
```c
int main(void) {
  int* ints = arr_new(10, sizeof(int));
  for (int i = 0; i < arr_len(ints); i++) {
    ints[i] = i;
  }
}
```

**arr_from**

```c
array_t arr_from(void* arr, int n, size_t size);
```
Allocates a new array on the heap, initialized with content from `arr`.

*Example*
```c
int main(void) {
  int* ints = arr_from((int[]) {1, 2, 3, 4, 5}, 5, sizeof(int));
  for (int i = 0; i < arr_len(ints); i++) {
    printf("%d\0", ints[i]);
  }
}
```

**arr_len**

```c
int arr_len(array_t arr);
```
Returns the length of an array. The array must have been allocated with
`arr_new` or `arr_from` as this function simply reads the header and returns it.

**arr_free**

```c
int arr_free(array_t arr);
```
Frees the array that was allocated through `arr_new` or `arr_from`. This is
necessary as it will free the correct pointer at the start of the header, not
the pointer to the data that the user has access to.
