// FUNC_NAME: SlotArrayManager::insert
uint __fastcall SlotArrayManager::insert(uint index, const SlotData* data) // data pointer passed in ESI by caller
{
    uint currentSize = g_slotCount;

    // Max capacity check (32 slots)
    if (currentSize > 31)
    {
        return currentSize & 0xFFFFFF00; // error/invalid handle
    }

    if (index != currentSize)
    {
        // Shift elements to make room at index
        // Copy last element into current position? Actually copies from a different array set?
        // The arrays seem to be split: first 8 bytes at g_slotData1, last 4 bytes at g_slotData2.
        // But the initial copy copies from g_sourceData1 and g_sourceData2 to the last slot?
        // This is a swap pattern to move the last element to the end before shifting.
        *(uint64*)(&g_slotData1[currentSize * 3]) = *(uint64*)(&g_sourceData1[currentSize * 12]); // 12-byte offset? Actually mismatched
        *(uint32*)(&g_slotData2[currentSize * 12]) = *(uint32*)(&g_sourceData2[currentSize * 12]);

        uint tempSize = currentSize - 1;

        // Shift elements from index to tempSize down by one slot (12 bytes each)
        if (index < tempSize)
        {
            uint8* dst = (uint8*)(&g_slotData1 + tempSize * 3); // end of destination
            int count = tempSize - index;
            do
            {
                // Shift 12 bytes down (from (dst-12) to dst)
                *(uint64*)dst = *(uint64*)(dst - 12);
                *(uint32*)(dst + 8) = *(uint32*)(dst - 4);
                dst -= 12;
                count--;
            } while (count != 0);
        }

        g_slotCount++;
        // Write the new element at index
        *(uint64*)(&g_slotData1[index * 3]) = *data; // first 8 bytes
        *(uint32*)(&g_slotData2[index * 12]) = *(uint32*)((uint8*)data + 8); // last 4 bytes
    }
    else
    {
        // Append at end
        *(uint64*)(&g_slotData1[index * 3]) = *data;
        *(uint32*)(&g_slotData2[index * 12]) = *(uint32*)((uint8*)data + 8);
        g_slotCount++;
    }

    // Build handle from address of inserted element: (address >> 8) | 1
    return ((uint32)(&g_slotData1[index * 3]) >> 8) | 1;
}