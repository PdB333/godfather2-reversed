// FUNC_NAME: findAllMatchingInSlot

void __fastcall findAllMatchingInSlot(unsigned int slotIndex, int baseAddress, unsigned int searchKey, int* outIndices)
{
    // Each slot occupies 0x168 bytes; offset 0x10 is a pointer to an indirection array.
    int slotOffset = (slotIndex & 0xFF) * 0x168;
    int* headerArray = (int*)(baseAddress + 0x10 + slotOffset);

    int firstIndex = *headerArray;
    if (firstIndex == 0)
        return;

    // The first element of headerArray is an index into the same array,
    // the value at that index is a pointer to the actual data structure.
    int dataPtr = headerArray[firstIndex];
    if (dataPtr == 0)
        return;

    // Data structure layout:
    // +0x00: unknown (probably padding or flags)
    // +0x02: unsigned short count (number of entries in the sorted array)
    // +0xBC: pointer to an array of entries, each entry is 0x80 bytes,
    //         first 4 bytes are the key (uint).
    unsigned short entryCount = *(unsigned short*)(dataPtr + 2);
    if (entryCount == 0)
        return;

    int entriesArray = *(int*)(dataPtr + 0xBC);  // pointer to entry array

    // Binary search for the first entry with key == searchKey
    int low = -1;
    int high = entryCount;
    int mid;
    while (low + 1 != high)
    {
        mid = (low + high) >> 1;
        // Mask index to 16 bits (likely safety for array bounds)
        unsigned int midIndex = (unsigned int)mid & 0xFFFF;
        unsigned int currentKey = *(unsigned int*)(entriesArray + midIndex * 0x80);
        if (currentKey < searchKey)
            low = mid;
        else
            high = mid;
    }

    // Collect all consecutive entries with matching key
    if (high < entryCount)
    {
        unsigned int index = (unsigned int)high & 0xFFFF;
        unsigned int firstKey = *(unsigned int*)(entriesArray + index * 0x80);
        if (firstKey == searchKey)
        {
            int outCount = 0;
            while (index < entryCount)
            {
                if (*(unsigned int*)(entriesArray + index * 0x80) != searchKey)
                    break;
                outIndices[outCount] = (int)index;  // store the entry index
                outCount++;
                index++;
            }
        }
    }
}