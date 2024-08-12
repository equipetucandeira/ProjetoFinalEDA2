#include "arvores.h"
#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define DECIMAL 10

#define DIGIT(n, p) (n / p) % DECIMAL

typedef myData T;

int CountingSort(T *, const size_t, int);

int RadixSortLSD(T *, const size_t);

static int GetMax(const T *array, const size_t size) {
  int max = array[0].codigo;

  for (size_t index = 0; index < size; ++index) {
    if (max < array[index].codigo) {
      max = array[index].codigo;
    }
  }

  return max;
}

int CountingSort(T *array, const size_t size, int exponent) {

  unsigned counting[DECIMAL];

  T *buffer = (T *)malloc(size * sizeof(T));

  if (buffer == NULL) {
    return ENOMEM;
  }

  memset(counting, 0, DECIMAL * sizeof(T));

  for (size_t index = 0; index < size; ++index) {
    ++counting[DIGIT(array[index].codigo, exponent)];
  }

  unsigned accumulation = 0;

  for (size_t index = 0; index < DECIMAL; ++index) {
    unsigned count = counting[index];

    counting[index] = accumulation;

    accumulation += count;
  }

  for (size_t index = 0; index < size; ++index) {
    buffer[counting[DIGIT(array[index].codigo, exponent)]++] = array[index];
  }

  memcpy(array, buffer, size * sizeof(T));

  free(buffer);

  exponent *= DECIMAL;

  return EXIT_SUCCESS;
}

int RadixSortLSD(T *array, const size_t size) {
  int max = GetMax(array, size);

  for (int exponent = 1; (max / exponent) > 0; exponent *= DECIMAL) {
    assert(CountingSort(array, size, exponent) == EXIT_SUCCESS);
  }

  return EXIT_SUCCESS;
}
