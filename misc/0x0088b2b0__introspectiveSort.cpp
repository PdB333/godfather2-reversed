// FUNC_NAME: introspectiveSort
// Address: 0x0088b2b0
// Introspective sort algorithm: performs a quicksort-like partition with depth limiting,
// then falls back to insertion sort for small arrays and heap sort for large ones.

void introspectiveSort(void* start, void* end, void* context)
{
    if (start == end) return;

    // Assuming 4-byte elements (common for pointers or integers in this engine)
    int elementSize = 4;
    int count = ((char*)end - (char*)start) / elementSize;

    // Compute maximum recursion depth (2*log2(count) - 2)
    int depthLimit = 0;
    int bitCount = count;
    while (bitCount) {
        depthLimit++;
        bitCount >>= 1;
    }
    depthLimit = depthLimit * 2 - 2;

    // Perform initial partitioning with depth limit (quicksort step)
    quicksortPartition(start, end, depthLimit, context); // FUN_0088a340

    if (count > 0x1c) { // More than 28 elements
        // Sort the first 28 elements using insertion sort
        void* firstEnd = (char*)start + 0x70; // 28 elements * 4 bytes = 0x70
        insertionSort(start, firstEnd, context); // FUN_00887730
        // Sort the remaining elements using heap sort
        heapSort(firstEnd, end, context);       // FUN_00887780
        return;
    }
    // Otherwise use insertion sort for the whole range
    insertionSort(start, end, context); // FUN_00887730
}