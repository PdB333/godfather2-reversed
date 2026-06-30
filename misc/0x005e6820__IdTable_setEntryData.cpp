// FUNC_NAME: IdTable_setEntryData
bool __cdecl IdTable_setEntryData(uint32 id, uint32 value1, uint32 value2) {
    // Only low 16 bits used for indexing, up to 512 entries
    if ((id & 0xFFFF) >= 0x200)
        return false;

    // Each entry is 0x30 bytes, starts at g_pIdTableBase + 0x10
    uint8* entryBase = (uint8*)g_pIdTableBase + 0x10 + (id & 0xFFFF) * 0x30;
    if (entryBase == nullptr)
        return false;

    // Verify the stored full ID matches (at entry offset +0x2C)
    uint32* pStoredId = (uint32*)(entryBase + 0x2C);
    if (*pStoredId != id)
        return false;

    // Write the two data values (offsets +0x24 and +0x28)
    uint32* pData0 = (uint32*)(entryBase + 0x24);
    uint32* pData1 = (uint32*)(entryBase + 0x28);
    *pData0 = value1;
    *pData1 = value2;

    return true;
}