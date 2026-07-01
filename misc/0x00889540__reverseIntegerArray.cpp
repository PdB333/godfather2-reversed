// FUNC_NAME: reverseIntegerArray
// Function at 0x00889540: Reverses an array of 32-bit integers in place using recursion.
void reverseIntegerArray(undefined4* startElement, int endAddress, undefined4 flags) {
    // Number of elements = (byte offset difference) / 4
    int elementCount = (endAddress - (int)startElement) >> 2;
    if (elementCount <= 1) {
        return;
    }
    // Pointer to the last element (just before endAddress)
    undefined4* lastElement = (undefined4*)(endAddress - 4);
    // Swap the first and last elements
    undefined4 temp = *lastElement;
    *lastElement = *startElement;
    *startElement = temp; // This assignment is inferred; the decompiled code may have omitted it.
    // Recursively reverse the interior subarray (excluding the swapped ends)
    // Call to FUN_008889c0 handles the inner reversal.
    // Parameters: startElement, offset=0, count-1, step=0, address of swapped temp, flags
    FUN_008889c0(startElement, 0, elementCount - 1, 0, &temp, flags);
}