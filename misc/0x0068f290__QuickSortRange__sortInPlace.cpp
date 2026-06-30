// FUNC_NAME: QuickSortRange::sortInPlace
void** __thiscall sortInPlace(void **outRange, void *start, void *end, void *pivotValue, int (*comparator)(void*, void*)) {
    int elementCount;
    int pivotIndex;
    void **midPtr;
    int compResult;
    void *leftResult;
    void *rightResult;

    elementCount = ((int)end - (int)start) >> 2; // number of 4-byte elements

    do {
        // outer loop: repeatedly partition until pivot found
        while (true) {
            pivotIndex = elementCount; // store current count
            if (pivotIndex < 1) {
                // empty range: return start as both boundaries
                outRange[0] = start;
                outRange[1] = start;
                return outRange;
            }
            elementCount = pivotIndex / 2; // new count = half
            midPtr = (void**)((int)start + elementCount * 4); // middle element
            compResult = comparator(*(int*)midPtr, *(int*)pivotValue);
            if (compResult == 0) break; // found element equal to pivot
            start = (void**)((int)midPtr + 4); // move start past midPtr
            elementCount = pivotIndex + (-1 - elementCount); // adjust count for right half
        }
        // check pivot relative to the equal element
        compResult = comparator(*(int*)pivotValue, *(int*)midPtr);
    } while (compResult != 0); // repeat if pivot is less than mid element

    // Recursively sort left and right partitions
    leftResult = sortInRange(outRange, start, midPtr, pivotValue, comparator);
    rightResult = sortInRange(outRange, (void**)((int)midPtr + 4), (void**)((int)start + pivotIndex * 4), pivotValue, comparator);
    outRange[0] = leftResult;
    outRange[1] = rightResult;
    return outRange;
}