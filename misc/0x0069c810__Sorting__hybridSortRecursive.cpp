// FUNC_NAME: Sorting::hybridSortRecursive
/* 
 * Function at 0x0069c810: Hybrid sorting algorithm with 40-element threshold.
 * Splits the array into multiple segments and delegates to base sort (FUN_0069c650) when size <= 40.
 * Operates on arrays of 8-byte elements (e.g., pairs of ints or pointers).
 * Parameters: 
 *   int* low - start of range
 *   int* mid - middle of range (used as pivot? )
 *   int* high - end of range
 * The splitting logic suggests median-of-three partitioning or multi‑pivot quicksort.
 */

void hybridSortRecursive(int* low, int* mid, int* high)
{
    int numElements = (high - low) >> 3; // number of 8-byte elements
    if (numElements > 0x28) {           // threshold: 40
        int lenAdjusted = numElements + 1;
        int pivotStep = lenAdjusted >> 3; // roughly numElements/8
        int* pivot1 = low + pivotStep * 2; // low + 2 * pivotStep (in bytes? actually pointer arithmetic adjusts by element size)
        // Actually pointer arithmetic on int* means shift by sizeof(int)=4, but the code uses byte offsets.
        // So we keep byte-level arithmetic.
        int* base1 = low + pivotStep * 8; // low + pivotStep * 8 bytes
        int* base2 = mid - pivotStep * 8; // mid - pivotStep * 8 bytes
        int* base3 = high - pivotStep * 8; // high - pivotStep * 8 bytes

        // Recursively sort four overlapping subranges
        baseSort(low, base1, pivot1);               // left-third
        baseSort(base2, mid, mid + pivotStep * 8);  // middle-left
        baseSort(high - pivotStep * 16, base3, high); // right-third
        baseSort(base1, mid, base3);                // combine central part?
    }
    else {
        baseSort(low, mid, high);
    }
}