// FUNC_NAME: EARSArray::growCapacity
void __thiscall EARSArray::growCapacity(int *arrayHandle, uint newCapacity)
{
    // arrayHandle[0]: pointer to element data (int*)
    // arrayHandle[1]: number of elements currently stored (uint)
    // arrayHandle[2]: allocated capacity (uint)
    // Each element is 0xC (12 bytes) in size
    uint oldCapacity = arrayHandle[2];
    if (oldCapacity < newCapacity) {
        // Allocate new buffer for newCapacity elements of 12 bytes each
        undefined8 *newData = (undefined8 *)FUN_009c8e80(newCapacity * 0xC);
        // Copy existing elements from old buffer to new buffer
        uint copied = 0;
        if (arrayHandle[1] != 0) {
            int srcOffset = 0;
            undefined8 *dst = newData;
            do {
                int srcPtr = *arrayHandle;
                if (newData != (undefined8 *)0x0) {
                    // Copy 8 bytes (first part of element)
                    *dst = *(undefined8 *)(srcPtr + srcOffset);
                    // Copy 4 bytes (second part of element)
                    *(undefined4 *)(dst + 1) = *(undefined4 *)((undefined8 *)(srcPtr + srcOffset) + 1);
                }
                copied++;
                srcOffset += 0xC;
                dst = (undefined8 *)((int)dst + 0xC);
            } while (copied < (uint)arrayHandle[1]);
        }
        // Free old buffer (if it existed)
        FUN_009c8f10(*arrayHandle);
        // Update handle with new buffer and capacity
        *arrayHandle = (int)newData;
        arrayHandle[2] = newCapacity;
    }
    return;
}