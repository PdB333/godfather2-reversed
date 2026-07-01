// FUNC_NAME: PlayerSM::initializeStateMachine
void __thiscall PlayerSM::initializeStateMachine(void* thisPtr) {
    // Set state to 2 (maybe idle or default state)
    *(int*)((char*)thisPtr + 0x14C) = 2;
    
    // If not already in state 1, set it and register a handler
    if (*(int*)((char*)thisPtr + 0x158) != 1) {
        *(int*)((char*)thisPtr + 0x158) = 1;
        // Register state handler at LAB_00978e00 for this object's state machine at +0x14
        registerStateCallback(thisPtr + 0x14, (void*)0x00978e00, 0);
    }
    
    // Advance to sub-state machine at offset 0x14
    void* subMachine = (char*)thisPtr + 0x14;
    // Register multiple state handlers for this sub-machine
    registerStateCallback(subMachine, (void*)0x0097ab30, 0);
    registerStateCallback(subMachine, (void*)0x00978dc0, 0);
    registerStateCallback(subMachine, (void*)0x0097ab70, 0);
    registerStateCallback(subMachine, (void*)0x00977610, 0);
}
