// FUNC_NAME: CrewManager::getCrewHandle
int __thiscall CrewManager::getCrewHandle(int crewId, int* outHandle)
{
    // Offset of crew entry array: +0x490 (5 entries, each 0x4a4 bytes)
    // Entry layout:
    //   +0x000: ? (offset 0x48C from computed base)
    //   +0x1CC: someValue (used as argument to global function call)
    //   +0x484: somePtr (if non-null, triggers global function call)
    //   +0x48C: crewId (compared with search ID)
    // Computed base = this + 4 + index * 0x4a4

    if (crewId == 0)
        return 0;

    for (int i = 0; i < 5; i++) {
        // The array starts at this+0x490, each entry is 0x4a4 bytes.
        // The ID field is at offset 0x48C within the entry.
        int* pEntryId = (int*)(this + 0x490 + i * 0x4a4); // points to entry ID
        if (crewId == *pEntryId) {
            // Found matching entry
            int* pEntryBase = (int*)(this + 4 + i * 0x4a4); // computed base for accessing other fields
            if (pEntryBase != nullptr) {
                int result = -1;
                if (*(int*)(pEntryBase + 0x484) != 0) {
                    // Call global manager method (vtable offset 0x68 from global pointer)
                    result = (*(int (__thiscall**)(int))(*DAT_01223510 + 0x68))(*(int*)(pEntryBase + 0x1CC));
                }
                *outHandle = result;
                return 1;
            }
        }
    }
    return 0;
}