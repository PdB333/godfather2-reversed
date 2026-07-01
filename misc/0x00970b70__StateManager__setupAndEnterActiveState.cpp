// FUNC_NAME: StateManager::setupAndEnterActiveState
void __thiscall StateManager::setupAndEnterActiveState(StateManager* this) {
    int currentState = *(int*)((unsigned char*)this + 0xdc);
    if (currentState != 3) {
        // Reset some flags
        *(int*)((unsigned char*)this + 0xc4) = 0;
        *(int*)((unsigned char*)this + 0xd4) = 0;

        // Choose substate based on current state
        int substate;
        switch (currentState) {
        case 1:
        case 6:
            substate = 9;
            break;
        default:
            substate = 10;
            break;
        }
        *(int*)((unsigned char*)this + 0xd8) = substate;

        // Hide ready state if transitioning from state 4
        if (currentState == 4) {
            DebugLog("HideReadyState", 0, &g_LogBuffer, 0);
        }

        // Perform state-specific startup
        if (currentState == 1) {
            // Some global initialization
            doSomeGlobalSetup();
        }

        // Register state transition handlers (likely adding callback sets)
        int* handlerBase = (int*)((unsigned char*)this + 0x10);
        registerHandler(handlerBase, &handler_set1, 1);
        registerHandler(handlerBase, &handler_set2, 1);
        registerHandler(handlerBase, &handler_set3, 1);
        registerHandler(handlerBase, &handler_set4, 1);

        // Mark state as active (3)
        *(int*)((unsigned char*)this + 0xdc) = 3;

        // Additional activation processing
        doPostActivation();
    }

    // Common teardown and display logic
    DebugLog("Destroy", 0, &g_LogBuffer, 0);
    DebugLog("ShowSetUp", 0, &g_LogBuffer, 0);

    // Call virtual method from vtable (probably something like onStateEntered)
    void** vtable = *(void***)((unsigned char*)this + 0x508);
    void (*virtualMethod)(int) = (void (*)(int))vtable[0x6c / 4]; // offset 0x6c in vtable
    *(char*)((unsigned char*)this + 0x554) = 0;
    virtualMethod(0);
}