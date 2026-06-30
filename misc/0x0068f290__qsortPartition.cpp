// FUNC_NAME: qsortPartition
// Address: 0x0068f290
// Internal partitioning function for quicksort used in Godfather 2.
// Uses a fixed pivot value and returns two partition pointers for recursion.
// The comparator returns false (0) if first < second, true (non-zero) otherwise.

typedef bool (__cdecl *Comparator)(int a, int b); // returns true if a < b

// Function signature from Ghidra: undefined4 * __cdecl qsortPartition(undefined4 *pResult, undefined4 *pStart, int pEndInt, undefined4 *pivot, Comparator compare)
// pResult: output array of two int pointers (left partition start, right partition start)
// pStart: pointer to start of array segment
// pEndInt: end address cast to int (one past last element)
// pivot: pointer to the pivot value (used for all comparisons)
// compare: comparison callback

int** __cdecl qsortPartition(int** pResult, int* pStart, int* pEnd, int* pivot, Comparator compare) {
    int count = (pEnd - pStart) >> 2; // number of ints
    int* currentStart = pStart;
    int remaining = count;

    while (true) {
        int midIndex = remaining / 2;
        if (midIndex < 1) {
            pResult[0] = currentStart;
            pResult[1] = currentStart;
            return pResult;
        }
        int* midPtr = currentStart + midIndex;
        // Check if middle element is less than pivot
        if (!compare(*midPtr, *pivot)) { // mid >= pivot
            // Check if pivot is less than middle element
            if (compare(*pivot, *midPtr)) {
                break; // pivot < mid: partition point found
            }
            // Equal: break as well (pivot equals mid element)
            break;
        } else {
            // Mid element < pivot: move start to after mid
            currentStart = midPtr + 1;
            remaining = remaining - 1 - midIndex;
        }
    }

    // Recursively sort left and right partitions using external functions
    // (these are thunks to the same partition function for left and right sides)
    int* leftHalf = FUN_0068eda0(currentStart, midPtr, pivot, compare, 0);
    int* rightHalf = FUN_0068ee00(midPtr + 1, pStart + count, pivot, compare, 0);
    pResult[0] = leftHalf;
    pResult[1] = rightHalf;
    return pResult;
}