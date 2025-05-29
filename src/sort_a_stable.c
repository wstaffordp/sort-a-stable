#include "sort_a_stable.h"

void sort_a_stable_ascending(uintptr_t input_count, int *input) {
  int input_capture;
  uintptr_t gap;
  uintptr_t i = 1;
  uintptr_t j;
  uintptr_t k = 0;

  if (input_count < 200) {
    while (i < input_count) {
      input_capture = input[i];
      j = i;

      while (
        j > 0 &&
        input[k] > input_capture
      ) {
        input[j] = input[k];
        j = k;
        k--;
      }

      input[j] = input_capture;
      k = i;
      i++;
    }

    return;
  }

  while (i < input_count) {
    if (input[i - 1] <= input[i]) {
      i++;
      continue;
    }

    input_capture = input[i];
    j = i;

    if (input[0] <= input_capture) {
      k = i;

      while (input[k - 1] > input_capture) {
        k >>= 1;
      }

      if (j > k) {
        gap = (k >> 3) + (k >> 2) + 1;
        k <<= 1;

        while (input[k - gap] > input_capture) {
          k -= gap;
          gap = (k >> 1) + 1;
        }

        while (gap > (input_count >> 6)) {
          gap >>= 1;

          while (input[k - gap] > input_capture) {
            k -= gap;
            gap = (k >> 1) + 1;
          }
        }

        while (input[k - 1] > input_capture) {
          k--;
        }

        while (j > k) {
          input[j] = input[j - 1];
          j--;
        }

        input[j] = input_capture;
      }

      i++;
      continue;
    }

    while (j > 0) {
      input[j] = input[j - 1];
      j--;
    }

    input[j] = input_capture;
    i++;
  }
}

void sort_a_stable_descending(uintptr_t input_count, int *input) {
  int input_capture;
  uintptr_t gap;
  uintptr_t i = 1;
  uintptr_t j;
  uintptr_t k = 0;

  if (input_count < 200) {
    while (i < input_count) {
      input_capture = input[i];
      j = i;

      while (
        j > 0 &&
        input[k] < input_capture
      ) {
        input[j] = input[k];
        j = k;
        k--;
      }

      input[j] = input_capture;
      k = i;
      i++;
    }

    return;
  }

  while (i < input_count) {
    if (input[i - 1] >= input[i]) {
      i++;
      continue;
    }

    input_capture = input[i];
    j = i;

    if (input[0] >= input_capture) {
      k = i;

      while (input[k - 1] < input_capture) {
        k >>= 1;
      }

      if (j > k) {
        gap = (k >> 3) + (k >> 2) + 1;
        k <<= 1;

        while (input[k - gap] < input_capture) {
          k -= gap;
          gap = (k >> 1) + 1;
        }

        while (gap > (input_count >> 6)) {
          gap >>= 1;

          while (input[k - gap] < input_capture) {
            k -= gap;
            gap = (k >> 1) + 1;
          }
        }

        while (input[k - 1] < input_capture) {
          k--;
        }

        while (j > k) {
          input[j] = input[j - 1];
          j--;
        }

        input[j] = input_capture;
      }

      i++;
      continue;
    }

    while (j > 0) {
      input[j] = input[j - 1];
      j--;
    }

    input[j] = input_capture;
    i++;
  }
}
