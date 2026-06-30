// FUNC_NAME: binarySearchUpperBound (or binarySearch)
// Function at 0x0068ee00: Performs a binary search for the upper bound of a key in a sorted array of 32-bit integers.
// Uses a user-supplied comparator function that takes two ints and returns char (0 for "key >= element"? see logic).
// Returns pointer to the first element that is strictly greater than the key (according to comparator).
int __cdecl binarySearchUpperBound(int* basePtr, int* endPtr, const int* keyPtr, char (__cdecl *comparator)(int, int)) {
    int rangeSize = (endPtr - basePtr); // number of elements = (endPtr - basePtr) / 4 but stored as raw pointer difference?
    // Actually param_2 - param_1 is byte difference, then >>2 => number of elements.
    // Let's compute correctly: rangeSize = (endPtr - basePtr) >> 2;  // each element is 4 bytes
    int rangeSize = ((int)endPtr - (int)basePtr) >> 2;

    while (int remaining = rangeSize, remaining > 0) {
        int midIdx = remaining / 2;
        char cmpResult = comparator(*keyPtr, basePtr[midIdx]);

        if (cmpResult == '\0') { // If comparator returns 0 (key >= element?), move to right half
            basePtr = basePtr + (midIdx + 1); // skip mid and left part
            rangeSize = remaining - midIdx - 1; // new size is right half
        } else {
            // If comparator returns non-zero (key < element?), keep left half
            rangeSize = midIdx; // new size is left half (including mid? actually midIdx is the count of elements left of mid)
        }
    }
    return (int)basePtr;
}