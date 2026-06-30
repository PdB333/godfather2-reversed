// FUNC_NAME: applySettingFromRegistry
void applySettingFromRegistry() {
    // this (ESI) pointer: the setting manager object (non-null)
    if (this != 0) {
        // Try to fetch an integer setting from the global parameter store by hash
        uint* storeEntry = (uint*)GetParameterStoreEntry(0xb6495298); // hash for "someSetting"
        if (storeEntry != 0 && storeEntry[5] == 2) { // storeEntry[5] == type integer
            int value = storeEntry[0]; // first field = value
            // Write current and previous value to the target structure (pointed by EDI)
            // Offsets +0x58 and +0x5c correspond to m_currentValue and m_previousValue
            *(int*)(reinterpret_cast<char*>(unaff_EDI) + 0x58) = value;
            *(int*)(reinterpret_cast<char*>(unaff_EDI) + 0x5c) = value;
            return;
        }
        // Fallback: try an alternate setting hash
        storeEntry = (uint*)GetParameterStoreEntry(0x136decc4); // hash for "alternateSetting"
        if (storeEntry != 0 && storeEntry[5] == 2) {
            int value = (*(int (__thiscall *)(int))0x0110ac08)(storeEntry[0]); // convert via function pointer
            *(int*)(reinterpret_cast<char*>(unaff_EDI) + 0x58) = value;
            *(int*)(reinterpret_cast<char*>(unaff_EDI) + 0x5c) = value;
        }
    }
}