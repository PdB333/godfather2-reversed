// FUNC_NAME: introsort8 (generic introsort for 8-byte elements)
// Address: 0x0069cd70
// Role: Hybrid introsort (quicksort until depth limit, then heapsort; for small runs use insertion sort)
// Element size is assumed to be 8 bytes (pointers or 64-bit values).

extern void partition(void** outLeftEnd, void** outRightStart, void* start, void* end);
extern void insertionSort(void* start, void* end, int unused);
extern void heapSort(void* start, void* end, int unused, int unused2);
extern void someSort(void* start, void* end); // possibly a fallback insertion or shell sort

void introsort8(void* start, void* end, int depthLimit)
{
    int currentRangeSize;

    currentRangeSize = (int)((char*)end - (char*)start); // byte difference

    do {
        currentRangeSize = currentRangeSize >> 3; // number of 8-byte elements

        // Small array? Use insertion sort (size < 33)
        if (currentRangeSize < 0x21) {
            if (1 < currentRangeSize) {
                insertionSort(start, end, 0);
            }
            return;
        }

        // Depth limit exhausted -> fallback to heapsort
        if (depthLimit < 1) {
            if (0x20 < currentRangeSize) {
                if (8 < (int)((char*)end - (char*)start & 0xfffffff8U)) {
                    heapSort(start, end, 0, 0);
                }
                someSort(start, end);
            } else {
                // small enough for insertion sort (already covered above but here for completeness)
                if (1 < currentRangeSize) {
                    insertionSort(start, end, 0);
                }
            }
            return;
        }

        // Partition the range around a pivot
        void* leftEnd = nullptr;
        void* rightStart = nullptr;
        partition(&leftEnd, &rightStart, start, end);

        // Recurse on the smaller partition first, then iterate over the larger
        // depthLimit reduced by a factor ~0.75 (derived from param_3 = param_3/2 + (param_3/2)/2)
        depthLimit = depthLimit / 2 + (depthLimit / 2) / 2;

        // Compare size of left partition vs right partition
        int leftSize = (int)((char*)leftEnd - (char*)start & 0xfffffff8U);
        int rightSize = (int)((char*)end - (char*)rightStart & 0xfffffff8U);

        if (leftSize < rightSize) {
            introsort8(start, leftEnd, depthLimit);
            start = rightStart; // continue with the larger right part
        } else {
            introsort8(rightStart, end, depthLimit);
            end = leftEnd; // continue with the larger left part
        }

        currentRangeSize = (int)((char*)end - (char*)start);
    } while (true);
}