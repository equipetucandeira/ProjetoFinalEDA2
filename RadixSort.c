#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "arvores.h"

#define DECIMAL 10

#define DIGIT(n, p) (n / p) % DECIMAL

typedef int T;

int CountingSort(T *, const size_t,int);

int RadixSortLSD(T *, const size_t);

static T GetMax(const T *array, const size_t size) {
  T max = array[0];

  for (size_t index = 0; index < size; ++index) {
    if (max < array[index]) {
      max = array[index];
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

  memset(counting,0,DECIMAL * sizeof(T));

  for (size_t index = 0; index < size; ++index) {
    ++counting[DIGIT(array[index], exponent)];
  }

  unsigned accumulation = 0;

  for (size_t index = 0; index < DECIMAL; ++index) {
    unsigned count = counting[index];

    counting[index] = accumulation;

    accumulation += count;
  }

  for (size_t index = 0; index < size; ++index) {
    buffer[counting[DIGIT(array[index], exponent)]++] = array[index];
  }

  memcpy(array, buffer, size * sizeof(T));

  free(buffer);
  exponent *= DECIMAL;

  return EXIT_SUCCESS;
}


int RadixSortLSD(T *array, const size_t size) {
  T max = GetMax(array, size);

  for (int exponent = 1; (max / exponent) > 0; exponent *= DECIMAL) {
    assert(CountingSort(array, size,exponent) == EXIT_SUCCESS);
  }

  return EXIT_SUCCESS;
}
