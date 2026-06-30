// FUNC_NAME: ObjectList::processEntries
void __thiscall ObjectList::processEntries(undefined4 *context) {
    char isAllMode;

    // Call a predicate on the context to determine processing mode
    isAllMode = (**(code (__thiscall **)(undefined4*))*context)(context);
    if (isAllMode == '\0') {
        // Process all entries regardless of flags
        uint idx = 0;
        if (m_entryCount != 0) {
            int entryOffset = 0;
            do {
                // Call virtual function at vtable offset 0x7c on each object entry
                (**(code (__thiscall **)(int))(**(int **)(m_entries + entryOffset) + 0x7c))(context);
                idx++;
                entryOffset += 16; // Each entry is 16 bytes
            } while (idx < m_entryCount);
        }
    } else {
        // Process only entries with the active flag set (bit 1 of flags byte)
        uint idx = 0;
        if (m_entryCount != 0) {
            int entryOffset = 0;
            do {
                Entry *entry = (Entry *)(m_entries + entryOffset);
                if ((*(byte *)(entry + 1) & 2) != 0) { // Check flags byte at entry+4, bit 1
                    (**(code (__thiscall **)(int))(*(int *)*entry + 0x7c))(context);
                }
                idx++;
                entryOffset += 16;
            } while (idx < m_entryCount);
        }
    }
}