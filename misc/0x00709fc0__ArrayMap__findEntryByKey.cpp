// FUNC_NAME: ArrayMap::findEntryByKey
void* __thiscall ArrayMap::findEntryByKey(int key) const
{
    // +0x25C: number of entries in the array
    uint count = *(uint*)(this + 0x25C);
    if (count == 0) return 0;

    // +0x04: start of the array of entries (each entry = 0x14 bytes)
    // Entry layout:
    //   +0x00: int key
    //   +0x04: data (16 bytes)
    int* pEntryKey = (int*)(this + 4);
    for (uint i = 0; i < count; i++)
    {
        if (key == *pEntryKey)
        {
            // Return pointer to the data portion of the matching entry
            return (void*)(this + 8 + i * 0x14);
        }
        pEntryKey += 5; // advance to next entry (5 ints = 0x14 bytes)
    }
    return 0;
}