// FUNC_NAME: activateEntityFromId
bool activateEntityFromId(uint32 fullId) {
    uint16 index = (uint16)(fullId & 0xFFFF);
    if (index >= 0x200) {
        return false;
    }

    // g_pEntityManagerGlobal points to a manager structure that holds an array of entity entries
    // starting at offset 0x10; each entry is 0x30 bytes with the full ID at offset 0x2c.
    uint8* pEntry = (uint8*)g_pEntityManagerGlobal + 0x10 + (index * 0x30);
    if (*(uint32*)(pEntry + 0x2c) != fullId) {
        return false;
    }

    // Attempt to activate/process the entry; returns non-zero on success.
    bool bActivated = processEntityEntry(index, 0);
    return bActivated;
}