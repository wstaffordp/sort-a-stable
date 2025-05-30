# Sort A Stable

It's a fast, in-place, non-auxiliary, stable sorting algorithm.

`sort_a_stable_ascending()` and `sort_a_stable_descending()` are the stable sorting functions that sort elements in either ascending or descending order while preserving original sort order context.

They accept the following 2 arguments in left-to-right order.

1. `input_count` is the count of elements in `input`.
2. `input` is the array of elements to sort.

It's in the same class as Bubble Sort, Insertion Sort and Stable Binary Insertion Sort.

It's the fastest stable sorting algorithm that doesn't require substantial auxiliary space for sorted runs or unsorted subarrays.

I welcome submissions of algorithms in the same class that challenge the aforementioned claim.

The following security explanation uses the context of ascending sort order.

`input_count < 200` ensures all sorting instances with less than `200` elements use a fast optimization of Insertion Sort to compensate for the conditional statement.

Other sorting instances fall through to a stable, unique Binary Insertion Sort derivative with one-way searching at specific offset calculations based on both the `high` bounds of sorted data and `input_count`.

`200` was selected as the lowest `input_count` that's faster than unoptimized Insertion Sort on average in speed tests.

`if (input[i - 1] <= input[i])` skips through sorted runs quickly for larger input sizes, making it faster for mostly-sorted and sorted arrays.

The unsorted element to insert in its sorted place is stored in `input_capture`.

`if (input[0] <= input_capture)` verifies that the element to insert isn't less than or equal to the first array element, otherwise it falls through to an Insertion Sort operation with less comparisons as it swaps all elements until reaching `0`.

When the first element is the smallest element compared to `input_capture`, the `high` bound `k` is decreased by half until reaching a point where `input_capture` is less than the element at index `k`.

`while (input[k - 1] > input_capture)` ensures that each adjacent, sorted element is never skipped before halving the index `k` with `k >>= 1`.

When `k` overshoots the insertion point, it calculates a `gap` starting point at an offset that's near 37.5% of the decreased, overshot `high` bound `k` by using `gap = (k >> 3) + (k >> 2) + 1`, then it doubles `k` to reset it back to a position where `input_capture` is less than or equal to the element at the high bound `k`.

The doubling of `k` is always safely within the bounds of `input_count` because the conditional statement `if (j > k)` verifies that `k` was already halved at least once.

Then, it performs a one-way Binary Search that decreases `k` by `gap` and decreases `gap` by `(gap >> 1) + 1`.

`gap` is always much smaller than `k`, so `k -= gap` always decreases safely within bounds.

`while (input[k - gap] > input_capture)` always breaks out of the loop because `input[0]` is already validated as less than or equal to `input_capture`.

The following demonstration proves the aforementioned safety by testing each possible `input_count` value up to approximately 1 billion.

``` c
#include <stdint.h>
#include <stdio.h>

int main(void) {
  uintptr_t i = 100;
  uintptr_t j;
  uintptr_t gap;
  uintptr_t out_of_bounds_error_count = 0;

  while (i < 1111111111) {
    j = i >> 1;
    gap = (j >> 3) + (j >> 2) + 1;
    j <<= 1;

    while (
      gap > 1 &&
      (j - gap) > 0
    ) {
      j -= gap;
      gap = (j >> 1) + 1;
    }

    if (j == 0) {
      out_of_bounds_error_count++;
    }

    i++;
  }

  if (out_of_bounds_error_count == 0) {
    printf("There are no out-of-bounds indices.\n");
  }

  return 0;
}
```

The next loop `while (gap > (input_count >> 6))` repeats the one-way Binary Search at a large-enough gap size relative to `input_count`.

`input_count >> 6` was chosen as a stopping bound because it yielded faster speeds on average than other shift values.

Then, `while (input[k — 1] > input_capture)` corrects the stability of the `k` index by decrementing `k--` until the correct insertion position is found.
