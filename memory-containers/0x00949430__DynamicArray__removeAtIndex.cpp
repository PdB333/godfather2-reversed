// FUNC_NAME: DynamicArray::removeAtIndex
// Function address: 0x00949430
// Removes an element at the given index from a dynamic array of 8-byte elements.
// The array structure: +0x00: pointer to elements, +0x04: current count (uint)

void __thiscall DynamicArray::removeAtIndex(uint index)
{
    // Only shift if the element is not the last one
    if (index < mCount - 1U) {
        undefined4* dst = (undefined4*)(mElements + index * 8);
        undefined4* src = (undefined4*)(mElements + 8 + index * 8);
        *dst = *src;           // Copy first 4 bytes
        dst[1] = src[1];       // Copy second 4 bytes
        index++;
        // Continue shifting until all following elements are moved
        // Note: original code uses a do-while loop, but functionally same as a while loop
        while (index < mCount - 1U) {
            dst = (undefined4*)(mElements + index * 8);
            src = (undefined4*)(mElements + 8 + index * 8);
            *dst = *src;
            dst[1] = src[1];
            index++;
        }
    }
    // Decrement count
    mCount--;
}