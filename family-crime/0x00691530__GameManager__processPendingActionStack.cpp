// FUNC_NAME: GameManager::processPendingActionStack
void __thiscall GameManager::processPendingActionStack(int param2) {
    int *pendingObject;
    
    if ((g_pGameManager->stateFlags != 0x12) && 
        (g_pendingActionIndex != -1) && 
        (g_pendingActionStack[g_pendingActionIndex] != 0)) {
        
        if ((param2 < 15) && (g_pGameManager->stateFlags != 0x12)) {
            // Call helper functions when param2 < 0xF and state allows
            someHelperFunction1(g_pGameManager->stateFlags);
            someHelperFunction2();
        }
        
        if (g_pendingActionIndex != -1) {
            pendingObject = g_pendingActionStack[g_pendingActionIndex];
            g_pendingActionIndex--;
        }
        
        // Get the vtable of the pending object and call its third virtual function (offset +8)
        int *vtablePtr = (int *)someHelperFunction1((byte)(g_pGameManager->stateFlags));
        (*(code *)(*vtablePtr + 8))(pendingObject);
    }
}