// FUNC_NAME: SharedPtrArray::assignRangeBackward
uint* SharedPtrArray::assignRangeBackward(int destStartOffset, uint* srcEndPtr)
{
    int elementCount = (int)srcEndPtr - destStartOffset >> 2; // Number of 4-byte entries
    uint* destPtr = (uint*)(destRangeEndBase - 4 + elementCount * 4); // destPtr points to end of destination range

    while (elementCount != 0) {
        srcEndPtr--;
        elementCount--;
        if (srcEndPtr != destPtr) {
            uint* oldPtr = (uint*)*destPtr;
            if (oldPtr != nullptr) {
                *oldPtr = *oldPtr - 1; // Decrement reference count
                if (*oldPtr == 0) {
                    releaseObject(*destPtr); // Free if no more references
                }
            }
            // Assign new pointer and increment its reference count
            *destPtr = (uint)*srcEndPtr;
            if (*srcEndPtr != 0) {
                **(uint**)*srcEndPtr = **(uint**)*srcEndPtr + 1;
            }
        }
        destPtr--;
    }
    return destPtr;
}