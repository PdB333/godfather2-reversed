// FUNC_NAME: InputManager::updateControllerStates
void InputManager::updateControllerStates()
{
    // Thread-local storage pointer (FS:[0x2C] -> TEB, +0x34 is a thread ID or flag)
    int* threadLocalPtr = *(int**)(__readfsdword(0x2C) + 0x2C);
    uint threadId = (uint)(*(int*)(threadLocalPtr + 0x34) != 0);
    
    // Save and set global thread-lock flag
    int savedLock = DAT_011f6be8[threadId];
    DAT_011f6be8[threadId] = 0xFFFFFFFF; // Lock
    
    FUN_0041f3d0(); // Begin input update
    
    if (g_numControllers != 0) {
        for (uint slot = 0; slot < g_numControllers; slot++) {
            ControllerInfo* info = &g_controllerInfo[slot];
            if (info->active == '\0' || g_disableInput == '\0') {
                // Reset button flags
                info->buttonStates[0x50] = 0;
                info->buttonStates[0x58] = 0;
                info->buttonStates[0x54] = 0;
                info->buttonStates[0x50] = 0; // Note: duplicate? likely intended for 0x50,0x54,0x58,0x5c
                
                uint buttonIndex = 0;
                int maxButtons = (info->active != '\0') * 2;
                if (maxButtons != -1) {
                    do {
                        char result = FUN_0041f620(slot, buttonIndex);
                        if (result != '\0') {
                            FUN_0041f9b0(buttonIndex);
                        }
                        buttonIndex++;
                    } while (buttonIndex < (uint)(maxButtons + 1));
                }
                
                // Reset rumble for slot 0 if multiple controllers
                if (slot == 0 && g_numControllers > 1) {
                    if (g_rumbleSize < 0x1000) {
                        RumbleData* rumble = &g_rumbleTable[g_rumbleSize];
                        rumble->state = 3; // Rumble stop
                    }
                }
            }
        }
    }
    
    FUN_0041faf0(); // End input update
    
    // Restore the lock flag
    DAT_011f6be8[threadId] = savedLock;
}