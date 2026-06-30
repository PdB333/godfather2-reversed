// FUNC_NAME: EA::Sort::Introsort
// Reconstructed C++ for function 0x00588250 - Introsort implementation (likely from EA EARS engine)
// Uses quicksort with fallback to heapsort for large depth, insertion sort for small partitions.

void Introsort(void* startPtr, void* endPtr, int depthLimit, CompareFunction comparFunc)
{
    int size;
    void* pivotLeft;
    void* pivotRight;

    size = (int)((char*)endPtr - (char*)startPtr) >> 2;  // element count (4-byte elements)

    for (;;) {
        if (size < 0x21) {
            // Small partition: use insertion sort if more than 1 element
            if (1 < size) {
                InsertionSort(startPtr, endPtr, comparFunc);
            }
            return;
        }

        if (depthLimit < 1) {
            // Depth limit exceeded: use heapsort for the remainder (if > 32 elements)
            if (0x20 < size) {
                if (4 < (int)((char*)endPtr - (char*)startPtr & 0xfffffffcU)) {
                    HeapSort(endPtr, comparFunc);
                }
                BuildHeap(comparFunc);  // Final heapify? Might be part of heapsort
            }
            return;
        }

        // Partition the array; returns two split points
        Partition(&pivotLeft, startPtr, endPtr, comparFunc);
        depthLimit = depthLimit / 2 + (depthLimit / 2) / 2;  // Reduce depth by ~25%
        size = (int)((char*)endPtr - (char*)pivotRight) >> 2;

        // Recurse on the smaller partition first (to limit stack depth)
        if ((int)((char*)pivotLeft - (char*)startPtr & 0xfffffffcU) < (int)((char*)endPtr - (char*)pivotRight & 0xfffffffcU)) {
            Introsort(startPtr, pivotLeft, depthLimit, comparFunc);
            startPtr = pivotRight;
        } else {
            Introsort(pivotRight, endPtr, depthLimit, comparFunc);
            endPtr = pivotLeft;
        }

        size = (int)((char*)endPtr - (char*)startPtr) >> 2;
    }
}