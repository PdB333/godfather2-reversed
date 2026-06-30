// FUNC_NAME: introsort_impl
void introsort_impl(char* start, char* end, int depthLimit) {
    int size;
    char* pivot;
    char* pivotPlusOne;

    size = end - start;
    while (true) {
        size = size >> 3;  // number of 8-byte elements
        if (size < 0x21) {  // small subarray => insertion sort
            if (size > 1) {
                insertionSort(start, end, 0);
            }
            return;
        }
        if (depthLimit < 1) {  // recursion depth exhausted
            if (size > 0x20) {  // still large -> use heapsort
                if (((int)(end - start) & 0xfffffff8U) > 8) {
                    heapSort(start, end, 0, 0);
                }
                finalSort(start, end);
            } else {
                if (size > 1) {
                    insertionSort(start, end, 0);
                }
            }
            return;
        }

        // Partition and update depth limit
        partition(&pivot, start, end);
        pivotPlusOne = pivot + 8;  // assume 8-byte elements
        depthLimit = depthLimit / 2 + (depthLimit / 2) / 2;  // 3/4 of original

        // Recurse on the smaller subarray first, then loop on the larger
        if ((pivot - start) < (end - pivotPlusOne)) {
            introsort_impl(start, pivot, depthLimit);
            start = pivotPlusOne;
        } else {
            introsort_impl(pivotPlusOne, end, depthLimit);
            end = pivot;
        }
        size = end - start;
    }
}