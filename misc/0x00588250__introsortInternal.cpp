// FUNC_NAME: introsortInternal
// Function at 0x00588250: Standard EA introsort algorithm for 32-bit elements.
// Parameters:
//   param_1 (base) - pointer to the first element
//   param_2 (end)  - pointer to one past the last element
//   param_3 (depthLimit) - maximum recursion depth
//   param_4 (comparator) - opaque data used by comparison routines

void introsortInternal(int* base, int* end, int depthLimit, void* comparator)
{
    int sizeBytes; // element count in bytes, then shifted to count
    int* leftEnd;
    int* rightStart;

    sizeBytes = (char*)end - (char*)base; // byte difference

    do {
        int elementCount = sizeBytes >> 2; // number of 4-byte elements

        if (elementCount < 0x21) { // 33 elements or fewer
            if (elementCount > 1) {
                // Insertion sort for small subarrays
                insertionSort(base, end, comparator);
            }
            return;
        }

        // If depth limit exhausted, fall back to heap sort
        if (depthLimit < 1) {
            if (elementCount > 0x20) {
                if ( (sizeBytes & 0xfffffffcU) > 4 ) { // at least one element remains
                    heapSort(end, comparator);
                }
                finalSort(comparator);
            }
            return;
        }

        // Partition the array, returns boundaries of the two partitions
        partition(&leftEnd, base, end, comparator);
        sizeBytes = (char*)rightStart - (char*)base; // update size from rightStart? Actually rightStart set by partition but not initialized above; careful: partition sets leftEnd and rightStart via output params
        // In the original: FUN_005885c0(&local_c, param_1, param_2, param_4); iVar1 = local_8;
        // So leftEnd (local_c) and rightStart (local_8) are computed.

        // Reduce depth limit: original depth * 3/4
        depthLimit = (depthLimit / 2) + (depthLimit / 2) / 2;

        int leftSize = (char*)leftEnd - (char*)base;
        int rightSize = (char*)end - (char*)rightStart;

        if (leftSize < rightSize) {
            // Recurse on smaller partition first to limit stack depth
            introsortInternal(base, leftEnd, depthLimit, comparator);
            // Then iterate on the larger partition
            base = rightStart;
            sizeBytes = (char*)end - (char*)rightStart;
        } else {
            introsortInternal(rightStart, end, depthLimit, comparator);
            end = leftEnd;
            sizeBytes = (char*)leftEnd - (char*)base;
        }
    } while (true);
}