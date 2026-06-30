// FUNC_NAME: introSort (generic introsort implementation)
// Address: 0x00588160
// Role: Introsort - a hybrid sorting algorithm that uses quicksort, switches to heapsort when recursion depth exceeds a limit, and uses insertion sort for small partitions.
// Parameters:
//   start - pointer to the first element (4-byte aligned)
//   end - pointer to one past the last element
//   depthLimit - maximum recursion depth (used to detect when to switch to heapsort)
//   compareFunc - comparison function or context (opaque pointer)
// Called functions:
//   partition (0x00588350) - partitions the range and returns pivot position and right partition start
//   insertionSort (0x00588510) - insertion sort for small ranges
//   heapSort (0x00588920) - heapsort for when depth limit is exceeded
//   finalizeSort (0x00588960) - cleanup after heapsort (possibly final insertion sort pass)

void __cdecl introSort(void* start, void* end, int depthLimit, void* compareFunc)
{
    int elementCount;
    void* pivotEnd;      // end of left partition (pivot position)
    void* rightStart;    // start of right partition

    // Calculate number of elements (assuming 4-byte elements)
    elementCount = (int)((char*)end - (char*)start) >> 2;

    do {
        // If the partition is small (less than 33 elements), use insertion sort
        if (elementCount < 0x21) {
            if (1 < elementCount) {
                insertionSort(start, end, compareFunc);
            }
            return;
        }

        // If recursion depth limit has been exhausted, switch to heapsort
        if (depthLimit < 1) {
            if (0x20 < elementCount) {
                // Only call heapsort if there are at least 2 elements (size > 4 bytes)
                if (4 < (int)((char*)end - (char*)start & 0xfffffffcU)) {
                    heapSort(end, compareFunc);
                }
                finalizeSort(compareFunc);
            }
            else {
                // Small partition after depth exhausted: use insertion sort
                if (1 < elementCount) {
                    insertionSort(start, end, compareFunc);
                }
            }
            return;
        }

        // Perform quicksort partition
        partition(&pivotEnd, start, end, compareFunc);
        // After partition, pivotEnd is the end of the left partition,
        // and rightStart is the start of the right partition (stored in local_8)
        // The code uses local_8 as the start of the right partition.
        // We need to retrieve it; the partition function likely sets it via a pointer.
        // For reconstruction, we assume partition sets both pivotEnd and rightStart.
        // In the original code, local_c = pivotEnd, local_8 = rightStart.
        // The following line is from the decompiled code: iVar1 = local_8;
        // So we assign rightStart from the partition output.
        // (The actual partition function signature would be something like:
        //  void partition(void** outPivot, void** outRightStart, void* start, void* end, void* compare);)
        // For simplicity, we assume partition sets these two values.
        // The code then uses rightStart (local_8) and pivotEnd (local_c).

        // Reduce depth limit: depthLimit = depthLimit/2 + (depthLimit/2)/2 = 3*depthLimit/4
        depthLimit = depthLimit / 2 + (depthLimit / 2) / 2;

        // Recurse on the smaller partition first to minimize stack depth
        if ((int)((char*)pivotEnd - (char*)start & 0xfffffffcU) < (int)((char*)end - (char*)rightStart & 0xfffffffcU)) {
            // Left partition is smaller: recurse on left, then continue loop on right
            introSort(start, pivotEnd, depthLimit, compareFunc);
            start = rightStart;
        }
        else {
            // Right partition is smaller (or equal): recurse on right, then continue loop on left
            introSort(rightStart, end, depthLimit, compareFunc);
            end = pivotEnd;
        }

        // Recalculate element count for the remaining partition
        elementCount = (int)((char*)end - (char*)start) >> 2;
    } while (true);
}