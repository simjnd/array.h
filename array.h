// -- HEADER -------------------------------------------------------------------

#ifndef ARRAY_H
#define ARRAY_H

typedef void* array_t;

array_t arr_new(int n, size_t size);
array_t arr_from(void* arr, int n, size_t size);
int arr_len(array_t arr);
int arr_free(array_t arr);

#endif

// -- IMPLEMENTATION -----------------------------------------------------------

#ifdef ARRAY_IMPL

#define _arr_alloc(n, size) malloc((n) * (size))
#define _arr_dealloc(p) free((p))

array_t arr_new(int n, size_t size) {
  int* p = _arr_alloc(n, size);
  if (p == NULL) return NULL;
  p[0] = n;
  p++;
  return (array_t) p;
}

array_t arr_from(void* arr, int n, size_t size) {
  array_t p = arr_new(n, size);
  if (p == NULL) return NULL;
  memcpy(p, arr, n * size);
  return p;
}

inline int arr_len(array_t arr) {
  return *(((int*) arr) - 1);
}

inline int arr_free(array_t arr) {
  _arr_dealloc(((int*) arr) - 1);
  return 0;
}

#endif
