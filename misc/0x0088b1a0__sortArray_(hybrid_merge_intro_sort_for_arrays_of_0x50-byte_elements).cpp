// FUNC_NAME: sortArray (hybrid merge/intro sort for arrays of 0x50-byte elements)
void sortArray(int startPtr, int endPtr, int comparisonParam)
{
    // If range is empty, nothing to sort
    if (startPtr == endPtr) {
        return;
    }
    
    // Number of elements (each element is 0x50 bytes)
    int elementCount = (endPtr - startPtr) / 0x50;
    
    // Compute depth = floor(log2(elementCount))
    int depth = 0;
    for (int temp = elementCount; temp != 0; temp >>= 1) {
        depth++;
    }
    
    // Call introspective sort with limited recursion depth (depth * 2 - 2)
    // This function likely handles small arrays efficiently (insertion/heap sort)
    FUN_0088a180(startPtr, endPtr, depth * 2 - 2, comparisonParam);
    
    // For large arrays (> 28 elements), split into two halves of 28 elements each
    // and recursively sort+merge each half
    if (elementCount > 28) {
        int midPtr = startPtr + 0x8c0; // 28 * 0x50 = 0x8c0
        // Sort/merge left half (startPtr to midPtr)
        FUN_008875a0(startPtr, midPtr, comparisonParam);
        // Sort/merge right half (midPtr to endPtr)
        FUN_00887610(midPtr, endPtr, comparisonParam);
    }
}