// FUNC_NAME: DynamicArray::assign
// Address: 0x0060f7f0
// Role: Assignment operator for a dynamic array of elements of size 0x14c (332 bytes).
// Each element structure: +0x00: dword, +0x04: dword, +0x08: dword, +0x0C: byte, +0x10: array of 0x4c dwords, +0x140: sub-object (12 bytes)
// The dynamic array structure: +0x00: data pointer, +0x04: size (count), +0x08: capacity

int * DynamicArray::assign(int *thisArray, int *srcArray) {
    int *result = thisArray;
    if (thisArray != srcArray) {
        // Destroy existing elements
        int count = thisArray[1];
        while (count-- > 0) {
            DestructElementAt(thisArray[0] + count * 0x14c); // FUN_00609aa0
        }
        // Reallocate if capacity insufficient
        if ((uint)thisArray[2] < (uint)srcArray[1]) {
            FreeMem(thisArray[0]); // FUN_009c8f10
            int newCapacity = srcArray[1];
            thisArray[2] = newCapacity;
            if (newCapacity == 0) {
                thisArray[0] = 0;
            } else {
                thisArray[0] = AllocateMem(newCapacity * 0x14c); // FUN_009c8e80
            }
        }
        // Copy elements
        int *destOff = 0; // Used as index offset
        int srcSize = srcArray[1];
        if (srcSize != 0) {
            int elementOffset = 0;
            do {
                int *destPtr = (int *)(thisArray[0] + elementOffset);
                if (destPtr != (int *)0x0) {
                    int *srcPtr = (int *)(srcArray[0] + elementOffset);
                    // Copy first 3 dwords
                    destPtr[0] = srcPtr[0];
                    destPtr[1] = srcPtr[1];
                    destPtr[2] = srcPtr[2];
                    // Copy byte at +0xC
                    *(char *)(destPtr + 3) = *(char *)(srcPtr + 3);
                    // Copy array of 0x4c dwords starting at +0x10
                    int *srcIter = (int *)((int)srcPtr + 0x10);
                    int *destIter = destPtr + 4;
                    for (int j = 0x4c; j > 0; j--) {
                        *destIter = *srcIter;
                        srcIter++;
                        destIter++;
                    }
                    // Copy sub-object at +0x140
                    CopySubObject((int *)((int)srcPtr + 0x140)); // FUN_0060faa0
                }
                elementOffset += 0x14c;
                destOff++;
            } while (destOff < srcSize);
        }
        // Update size
        thisArray[1] = srcArray[1];
    }
    return result;
}