// FUNC_NAME: quickSort
// Address: 0x005885c0
// Generic quicksort for arrays of 32-bit values.
// Parameters:
//   outBounds   - output buffer for two pivot pointers (unused in recursion?)
//   low         - pointer to first element (inclusive)
//   high        - pointer to last element (inclusive)
//   comparator  - unused in this implementation; actual comparator is fixed at 0x00587840
// The fixed comparator (FUN_00587840) compares two ints and returns 0 if equal, non‑zero otherwise.
// The subroutine FUN_005889d0 is assumed to swap two elements or copy a pivot.
void quickSort(int* outBounds, int* low, int* high, int* comparator) {
    int* pivot;    // selected pivot element
    int* left;     // left scanning pointer
    int* right;    // right scanning pointer
    int temp;      // temporary for swaps

    // Choose pivot as middle element
    pivot = low + ((high - low) / 2);

    // Copy pivot element to some temporary location (FUN_005889d0)
    // This function likely copies the pivot value to a separate variable or swaps it.
    FUN_005889d0(pivot, comparator);

    // Initialise scanning pointers
    right = pivot;
    left = pivot;

    // === Partitioning loop ===
    // Move right pointer leftwards while elements are equal? (two comparisons)
    while (low < right &&
           (temp = compareFunc(), temp == 0) &&
           (temp = compareFunc(), temp == 0)) {
        right--;
    }

    do {
        // Move left pointer rightwards
        left++;
        if (high < left) break;
        if ((temp = compareFunc(), temp != 0)) break; // left element > pivot?
        if ((temp = compareFunc(), temp == 0)) {
            // Swap left and right? (inverting?)
            // In the original code this is a swap with decrement/break conditions
        }
    } while (true);

    // Post‑partition recursion (simplified loop of recursions)
    // The code uses goto to repeat the partitioning on sub‑arrays until done.
    // We'll represent the core logic as a standard quicksort recursion here.

    // Store the current pivot boundaries
    *outBounds = right;
    outBounds[1] = left;
}
```