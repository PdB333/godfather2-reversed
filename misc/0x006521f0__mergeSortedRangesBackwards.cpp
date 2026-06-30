// FUNC_NAME: mergeSortedRangesBackwards
// Address: 0x006521f0
// Role: Merges two sorted subarrays into a destination buffer, writing from the end backwards.
// Parameters:
//   this (in_EAX): Pointer to one past the end of the destination buffer.
//   src1Start: Start of first sorted subarray.
//   src1End: End of first sorted subarray (exclusive).
//   src2Start: Start of second sorted subarray.
//   src2End: End of second sorted subarray (exclusive).
//   compare: Comparison function returning nonzero if a > b (strict ordering).
// Returns: Pointer to the beginning of the merged output.

undefined4* __thiscall mergeSortedRangesBackwards(undefined4* destEnd, undefined4* src1Start, undefined4* src2Start, undefined4* src2End, code* compare)
{
    char compareResult;
    undefined4* outputPtr;       // originally in_EAX
    undefined4* src2Cursor;
    int remainingCount;

    src2Cursor = src2End;

    if (src1Start != destEnd) {   // while there are elements in first range (destEnd is src1End here)
        do {
            // If second range is exhausted, copy remaining from first range
            if (src2Start == src2Cursor) {
                remainingCount = (int)destEnd - (int)src1Start >> 2;  // number of elements in first range
                outputPtr = destEnd + -remainingCount;                // destination for the block
                if (remainingCount < 1) return outputPtr;
                _memmove_s(outputPtr, remainingCount * 4, src1Start, remainingCount * 4);
                return outputPtr;
            }

            // Compare last elements of each range
            src2End = src2Cursor + -1;  // temporary decrement of src2End (overwritten)
            compareResult = (char)(*compare)(src2Cursor[-1], destEnd[-1]);

            outputPtr = destEnd + -1;
            if (compareResult == 0) {
                // Take from second range
                *outputPtr = *src2End;
            }
            else {
                // Take from first range
                *outputPtr = destEnd[-1];
                src2End = src2Cursor;   // revert src2End (no element taken from second)
                destEnd = destEnd + -1; // advance first range's end
            }
            src2Cursor = src2End;       // update cursor for second range
        } while (src1Start != destEnd);
    }

    // Copy remaining second range (if any)
    remainingCount = (int)src2End - (int)src2Start >> 2;
    outputPtr = destEnd + -remainingCount;
    if (remainingCount < 1) return outputPtr;
    _memmove_s(outputPtr, remainingCount * 4, src2Start, remainingCount * 4);
    return outputPtr;
}