// FUNC_NAME: EntryManager::isEntryActive
bool __thiscall EntryManager::isEntryActive(int thisPtr, uint targetId)
{
    // Array of entries starts at offset 0x18 from this
    // Each entry is 36 bytes (9 uint32s)
    // Entry struct: flags (uint32) at +0x00, id (uint32) at +0x04
    // flags bit0: active flag
    // flags bit1: in-use/pending flag (must be clear)
    uint* entryBase = (uint*)(thisPtr + 0x18);
    
    for (int i = 0; i < 7; i++)
    {
        uint* entry = entryBase + (i * 9); // 9 uint32s per entry
        uint flags = entry[0];
        uint id = entry[1];
        
        if (id == targetId && (flags & 1) && !(flags & 2))
        {
            return true;
        }
    }
    return false;
}