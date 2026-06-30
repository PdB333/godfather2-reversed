// FUNC_NAME: introsortNthElement
// Address: 0x00588160
// Role: Hybrid introsort (quicksort with depth limit fallback to heapsort) for array of 4-byte elements.
// The function sorts the range [param_1, param_2) using the comparison function param_4.
// param_3 controls recursion depth; when it becomes < 1, heapsort is used instead of further recursion.
// When the range is small (<= 33 elements), an insertion sort (FUN_00588510) is used.
void introsortNthElement(int* start, int* end, int depthLimit, int (*compare)(int*, int*)) // param_4: comparison function pointer
{
    int iVar1;
    int leftPartitionEnd;
    int rightPartitionStart;

    // Compute initial element count: (end - start) >> 2 (byte diff to element count)
    iVar1 = ((int)end - (int)start) >> 2;
    do {
        // If range is small enough, use insertion sort
        if (iVar1 < 0x21) {
LAB_005881f6:
            if (1 < iVar1) {
                insertionSort(start, end, compare); // FUN_00588510
            }
            return;
        }

        // If depth limit exhausted, fall back to heapsort
        if (depthLimit < 1) {
            if (0x20 < iVar1) {
                // If range > 128 elements, do a partial heapsort of the end?
                if (4 < (int)((int)end - (int)start & 0xFFFFFFFCU)) {
                    heapsortPartial(end, compare); // FUN_00588920
                }
                heapsortFull(compare); // FUN_00588960
            }
            goto LAB_005881f6;
        }

        // Partition the range around a pivot, store pivot-adjacent boundaries
        partition(&leftPartitionEnd, start, end, compare); // FUN_00588350
        iVar1 = rightPartitionStart; // Note: local_8 is uninitialized in the code? Actually local_8 is set by partition?
        // Decrease depth limit: depthLimit * 3/4
        depthLimit = depthLimit / 2 + (depthLimit / 2) / 2;

        // Recurse on the smaller partition first to limit stack depth
        if ((int)((int)leftPartitionEnd - (int)start & 0xFFFFFFFCU) < (int)((int)end - (int)rightPartitionStart & 0xFFFFFFFCU)) {
            introsortNthElement(start, leftPartitionEnd, depthLimit, compare);
            start = rightPartitionStart; // Continue sorting the right part in the loop
        } else {
            introsortNthElement(rightPartitionStart, end, depthLimit, compare);
            end = leftPartitionEnd; // Continue sorting the left part in the loop
        }
        iVar1 = (int)end - (int)start;
    } while (true);
}