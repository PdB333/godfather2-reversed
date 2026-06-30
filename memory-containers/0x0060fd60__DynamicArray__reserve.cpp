// FUNC_NAME: DynamicArray::reserve
// Function at 0x0060fd60: Resizes the internal buffer to accommodate at least 'newCapacity' elements.
// Element size is 0x14c (332 bytes). Structure: [mData (int*), mSize (int), mCapacity (int)].
void DynamicArray::reserve(int* container, uint newCapacity)
{
    // container[2] is current capacity
    if ((uint)container[2] < newCapacity)
    {
        // Allocate new buffer: newCapacity * elementSize (0x14c)
        int* newData = (int*)FUN_009c8e80(newCapacity * 0x14c);

        if (container[0] != 0) // old data exists
        {
            uint i = 0;
            if (container[1] != 0) // mSize > 0
            {
                // Pointers for copy: newElement starts at newData + 2 ints? Actually newData+8 bytes offset
                int* newElemBase = (int*)((char*)newData + 8);
                do
                {
                    // Old element pointer: container[0] + (i * 0x14c)
                    int* oldElem = (int*)((char*)container[0] + i * 0x14c);
                    // Copy first 3 ints (12 bytes) from old to new element
                    newElemBase[-2] = oldElem[0];
                    newElemBase[-1] = oldElem[1];
                    newElemBase[0] = oldElem[2];
                    // Copy 1 byte at offset 12 (0xC)
                    *(char*)(newElemBase + 1) = *(char*)(oldElem + 3);
                    // Copy remaining 0x4c ints (0x130 bytes) starting from oldElem+4 to newElemBase+2
                    int* src = oldElem + 4;
                    int* dst = newElemBase + 2;
                    for (int j = 0x4c; j != 0; j--)
                    {
                        *dst = *src;
                        src++;
                        dst++;
                    }
                    // Destroy sub-object at old element offset 0x50 (0x140 bytes)
                    FUN_0060faa0(oldElem + 0x50);
                    // Debug/assert call
                    FUN_00609aa0();
                    i++;
                    newElemBase += 0x53; // 0x53 ints = 0x14c bytes
                } while (i < (uint)container[1]);
            }
            // Free old buffer
            FUN_009c8f10(container[0]);
        }
        // Update container fields
        container[0] = (int)newData;
        container[2] = newCapacity; // capacity updated, size unchanged
    }
}