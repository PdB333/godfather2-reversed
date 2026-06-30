// FUNC_NAME: mergeSortedRanges (0x00652640)
// Merges two sorted ranges using a comparator, then copies remaining elements.
// The comparator returns 0 if the element from the first range should be taken,
// non-zero if the element from the second range should be taken.
// Additional stack parameters (param_7, param_8) are passed for copy operations and allocations.

typedef char (*Comparator)(void* elem1, void* elem2);

// Helper functions:
void processElement(void* element);                         // FUN_006523a0 - emits element to output
void* copyRange(void* dest, void* source, ...);            // FUN_00652100 - copies a range with alignment
void deallocate(void* ptr);                                 // FUN_009c8eb0 - frees memory

void* mergeSortedRanges(
    void* dest,                // param_1 - output buffer
    void** srcBegin1,          // param_2 - start of first sorted range
    void** srcEnd1,            // param_3 - end of first range
    void** srcBegin2,          // param_4 - start of second sorted range
    void** srcEnd2,            // param_5 - end of second range
    Comparator cmp,            // param_6 - comparison function
    int alignmentSize,         // param_7 - alignment for copy (in_stack_00000028)
    void* extraParam           // param_8 - additional parameter (in_stack_00000038)
)
{
    uint aligned;
    void* localBuffer[1];      // auStack_1c - temporary buffer for leftover copy
    void* localAlloc = nullptr; // iStack_18 - allocated memory pointer

    // Main merge loop: compare current elements and take one from the appropriate range
    while (srcBegin1 != srcEnd1 && srcBegin2 != srcEnd2) {
        // comparator is called with *srcBegin2, *srcBegin1 (order: second, first)
        char cmpResult = cmp(*srcBegin2, *srcBegin1);
        if (cmpResult == '\0') {
            // Take element from first range and advance it
            processElement(*srcBegin1);
            srcBegin1++;
        } else {
            // Take element from second range and advance it
            processElement(*srcBegin2);
            srcBegin2++;
        }
    }

    // After loop, align srcBegin2 to a 256-byte boundary (possibly for DMA copy)
    aligned = ((uint)srcBegin2 >> 8) << 8;
    srcBegin2 = (void**)aligned;

    // Copy remaining elements from first range (if any) into local buffer
    copyRange(localBuffer, srcEnd1, 0, 0, 0, 0, 0, extraParam, srcBegin2, srcBegin2, srcBegin2);
    if (localAlloc != nullptr) {
        deallocate(localAlloc);
    }

    // Re-align srcBegin2 (same operation)
    srcBegin2 = (void**)aligned;

    // Copy remaining elements from second range directly to destination
    copyRange(dest, srcEnd2, 0, 0, 0, 0, 0, alignmentSize, srcBegin2, srcBegin2, srcBegin2);
    if (alignmentSize != 0) {
        deallocate((void*)alignmentSize); // Note: original uses in_stack_00000028 as pointer
    }

    return dest;
}