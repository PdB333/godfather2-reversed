// FUNC_NAME: GodfatherGameManager::shutdownGame

// Function address: 0x005e3740
// Role: Shutdown/cleanup sequence for the game manager, called when exiting the game
// This function releases many global subsystems and resets pointers.

int GodfatherGameManager::shutdownGame(int param_1) // param_1 is 'this' (GodfatherGameManager*)
{
    int * puVar1;
    char cVar2;
    int * puVar3;

    puVar1 = g_globalPtr_01223514; // +0x0 global pointer, likely to a subsystem manager (e.g., InputManager)
    processEvents(); // FUN_005dbc10 - process pending events / update system
    cVar2 = isGameActive(); // FUN_005f0840 - check if game is still active
    if (cVar2 != '\0') {
        puVar3 = puVar1 + 2;
        puVar1[1] = 0;
        if (puVar3 != nullptr) {
            *puVar3 = 0;
            puVar1[3] = 0;
            *(short *)(puVar1 + 4) = 0;
            *(short *)((int)puVar1 + 0x12) = 0;
            processEvents(puVar3, 0); // shutdown specific subsystem
            shutdownInputSystem(); // FUN_005f2de0
        }
    }
    if (g_globalPtr_01223514 != nullptr) {
        // Call virtual destructor? vtable+0
        (*(code **)*g_globalPtr_01223514)[0x1](1); // virtual function with parameter 1
    }
    processEvents(); // second call
    if ((g_flag_011a0ee0 != 0) && (g_flag_011a0edc != 0)) {
        shutdownNetworkSystem(); // FUN_005f5910 - likely network cleanup
    }
    shutdownAudioSystem(); // FUN_005f1cc0
    shutdownEntitySystem(); // FUN_005e1e50
    if (g_globalPtr_0122350c != nullptr) {
        (*(code **)*g_globalPtr_0122350c)[0x1](1); // another virtual call
    }
    puVar1 = g_globalPtr_012234bc + 0x1804; // offset 0x1804, likely a child object pointer
    puVar3 = g_globalPtr_012234bc;
    if ((int *)g_globalPtr_012234bc[0x1804] != nullptr) {
        puVar3 = g_globalPtr_012234bc + 0x180f; // offset 0x180f, some count or flag
        if (g_globalPtr_012234bc[0x180f] != 0) {
            // Call method at vtable+4 with param 0
            (*(code **)(*(int *)g_globalPtr_012234bc[0x1804]))[0x2](g_globalPtr_012234bc[0x180f], 0);
            *puVar3 = 0; // clear the count
        }
        // Call method at vtable+0xc
        (*(code **)(*puVar1))[0x3]();
        puVar3 = g_globalPtr_012234bc;
        *puVar1 = 0;
    }
    if (puVar3 != nullptr) {
        // Call virtual destructor
        (*(code **)*puVar3)[0x0](0);
        if (*(int **)(param_1 + 4) != nullptr) { // this+0x4, some member pointer
            (*(code **)(**(int **)(param_1 + 4)))[0x2](puVar3, 0); // another virtual call
        }
    }
    shutdownUISystem(); // FUN_005e7320
    if (g_globalPtr_01223504 != nullptr) {
        (*(code **)*g_globalPtr_01223504)[0x1](1);
    }
    shutdownScriptEngine(); // FUN_005dc1a0
    if (g_globalPtr_01223508 != nullptr) {
        (*(code **)*g_globalPtr_01223508)[0x1](1);
    }
    (*(code **)(*g_globalPtr_01223510))[0x2](); // Call vtable+8 on some object
    if (g_globalPtr_01223510 != nullptr) {
        (*(code **)*g_globalPtr_01223510)[0x1](1); // destructor?
    }
    if (*(int **)(param_1 + 4) != nullptr) {
        (*(code **)(**(int **)(param_1 + 4)))[0x3](); // vtable+0xc
        *(int *)(param_1 + 4) = 0; // clear member pointer
        return 1;
    }
    return 0;
}