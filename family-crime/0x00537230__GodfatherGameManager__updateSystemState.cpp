// FUNC_NAME: GodfatherGameManager::updateSystemState
void GodfatherGameManager::updateSystemState() {
    // Global state flags, likely initialized elsewhere
    // s_someFlag1 = 0x011da7f0, s_someFlag2 = 0x011da7f4
    // g_gameManager = 0x01205750
    if (s_someFlag1 != 1) {
        // Call virtual function at vtable+0x198 with (0, 1) – possibly enable a mode
        (*(void(__thiscall *)(GodfatherGameManager*, int, int))(*((int**)this)[0x198 / 4]))(this, 0, 1);
        s_someFlag1 = 1;
    }
    if (s_someFlag2 != 0) {
        // Call virtual function at vtable+0x190 with (0, 0, 0, 0) – possibly reset state
        (*(void(__thiscall *)(GodfatherGameManager*, int, int, int, int))(*((int**)this)[0x190 / 4]))(this, 0, 0, 0, 0);
        s_someFlag2 = 0;
    }
}