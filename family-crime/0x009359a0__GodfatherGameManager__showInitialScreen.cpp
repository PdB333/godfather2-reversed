// FUNC_NAME: GodfatherGameManager::showInitialScreen
void __fastcall GodfatherGameManager::showInitialScreen(void* this)
{
    // Check if presentation manager is initialized (DAT_01129828[0xb] might be a flag)
    if (g_presentationManager[0xb] != 0) {
        FUN_008f1f40();  // Unknown initialisation
    }

    // If the screen-shown flag (+0xac) is not set
    if (*(char*)((int)this + 0xac) == '\0') {
        // Check if a specific input flag (bit 10) is set
        if ((g_inputFlags >> 10 & 1) != 0) {
            // Call presentation manager's method at vtable offset 0x1c (pushScreen?)
            (**(code**)(*g_presentationManager + 0x1c))(&LAB_00934a00, 0);
            *(char*)((int)this + 0xac) = 1;  // Mark screen as shown
            return;
        }

        // If input manager exists and has a certain flag (bit 0 of offset 6)
        if ((g_inputManager != 0) && ((*(unsigned char*)(g_inputManager + 6) & 1) != 0)) {
            // Set a UI state flag at offset 0x18 of g_uiState
            *(char*)(g_uiState + 0x18) = 1;
        }

        // Show default screen (different label)
        (**(code**)(*g_presentationManager + 0x1c))(&LAB_00935240, 0);
        *(char*)((int)this + 0xac) = 1;  // Mark screen as shown
    }

    return;
}