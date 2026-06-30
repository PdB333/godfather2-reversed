// FUNC_NAME: threeWayPartition

/**
 * Performs a three-way partition of an array segment for quicksort.
 * Arranges elements into three groups relative to the pivot (first element):
 * - Less than pivot (left)
 * - Equal to pivot (middle)
 * - Greater than pivot (right)
 * 
 * @param first  Pointer to the first element (used as pivot)
 * @param last   Pointer to one past the last element
 * @param comp   Comparator function returning:
 *               - negative if first arg < second
 *               - zero if equal
 *               - positive if first arg > second
 * 
 * @note The parameter order in the comparator is (element, pivot).
 *       This function is derived from Ghidra decompilation of FUN_00651690.
 *       Internal swap function is at 0x00652420.
 */
void threeWayPartition(int* first, int* last, char (*comp)(int, int))
{
    // If first == last or only one element, nothing to do
    if (first == last || first + 1 == last) {
        return;
    }

    int* low = first;        // Pivot (start of equal region)
    int* mid = first + 1;    // Scanning pointer (current element)
    int* high = first + 2;   // Boundary for greater region (moves ahead of mid)

    while (mid != last) {
        int result = comp(*mid, *first); // Compare current with pivot

        if (result == 0) {
            // Current element equals pivot
            // Search backward from high-2 to find an element not equal to pivot
            int* walker = high - 2;
            while (walker > first && comp(*mid, *walker) == 0) {
                walker--;
            }
            // If found non-equal element before mid, swap it with high-1
            if (walker != mid && mid != high) {
                swapElements(walker, high); // FUN_00652420
            }
        }
        else {
            // Current element is less than pivot (result != 0)
            // Swap low with high-1 to move small element to left
            if (first != mid && mid != high) {
                swapElements(low, high); // FUN_00652420
            }
        }

        mid++;
        high++;
    }
}

// External swap function (address 0x00652420)
void swapElements(int* a, int* b);