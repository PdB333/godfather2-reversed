// FUNC_NAME: DataManager::setDataByKey
// At 0x00965b20, this function looks up an entry by key in an array and writes two uint32 values.
// It also clears a field and sets a flag.
// Class layout (offsets from this):
// +0x3C4: int** m_entries  (array of pointers to entries)
// +0x3C8: uint32 m_entryCount
// +0x0C4: uint32 m_clearField
// +0x6F4: uint32 m_flags (bit0 = busy, bit2 = dirty)
// Entry struct:
// +0x00: uint32 data1
// +0x04: uint32 data2
// +0x5C: int32  key

extern bool g_isInitialized; // DAT_01223484

void __thiscall DataManager::setDataByKey(void* thisPtr, int key, uint32 value1, uint32 value2)
{
    // Early out if system not initialized or the busy flag is set
    if (!g_isInitialized) return;
    uint32* flagsPtr = (uint32*)((char*)thisPtr + 0x6F4);
    if (*flagsPtr & 1) return; // Bit0 means busy, skip operation

    uint32 count = *(uint32*)((char*)thisPtr + 0x3C8);
    if (count == 0) return;

    // Get base pointer to the array of entry pointers
    int** entries = *(int***)((char*)thisPtr + 0x3C4);

    uint32 index = 0;
    int** iter = entries;
    while (index < count)
    {
        int* entry = *iter;
        if (entry != nullptr)
        {
            int entryKey = *(int*)((char*)entry + 0x5C);
            if (entryKey == key)
            {
                // Found matching entry; write the two values
                uint32* targetData = (uint32*)entries[index]; // same as *iter
                if (targetData != nullptr)
                {
                    targetData[0] = value1;
                    targetData[1] = value2;

                    // Clear a field and set the dirty flag (bit2)
                    *(uint32*)((char*)thisPtr + 0xC4) = 0;
                    *flagsPtr |= 4;
                }
                return;
            }
        }
        iter++;
        index++;
    }
}