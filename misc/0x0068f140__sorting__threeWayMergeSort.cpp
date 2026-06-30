// FUNC_NAME: sorting::threeWayMergeSort

// Address: 0x0068f140
// Internal hybrid sort: uses 3-way recursive split when element count > 40,
// otherwise delegates to simpleSort (likely insertion sort for small arrays).
void threeWayMergeSort(int* start, int* mid, int* end, int* tempBuffer) {
    int elementCount = (end - start) >> 2; // byte offset / 4 -> number of ints
    if (elementCount > 0x28) { // 40 elements threshold
        int adjustedCount = elementCount + 1;
        // Compute block size: approximately (n+1)/8, with sign handling (always positive here)
        int blockSize = (adjustedCount + (adjustedCount >> 0x1f & 7)) >> 3;
        int* leftEnd = start + blockSize;          // start + iVar2 * 4
        int* leftFarEnd = start + 2 * blockSize;   // start + iVar2 * 8
        int* midStart = mid - blockSize;           // mid + iVar2 * -4
        int* midEnd = mid + blockSize;             // mid + iVar2 * 4
        int* rightMid = end - blockSize;           // end + iVar2 * -4
        int* rightStart = end - 2 * blockSize;     // end + iVar2 * -8

        // Recursively sort three overlapping subarrays (each of size 2*blockSize)
        simpleSort(start, leftEnd, leftFarEnd, tempBuffer);
        simpleSort(midStart, mid, midEnd, tempBuffer);
        simpleSort(rightStart, rightMid, end, tempBuffer);

        // Merge the three sorted subarrays
        simpleSort(leftEnd, mid, rightMid, tempBuffer);
        return;
    }
    // Base case: small array handled directly
    simpleSort(start, mid, end, tempBuffer);
}