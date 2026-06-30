// FUNC_NAME: DonControlGadget::isTimerActive
bool __fastcall DonControlGadget::isTimerActive(DonControlGadget* this) {
    void* stateMachinePtr;          // piVar1
    int currentState;               // iVar2

    // Check if gadget is active (field +0x18 likely m_bActive or m_pOwner)
    if (*(int*)((int)this + 0x18) == 0) {
        stateMachinePtr = nullptr;
    } else {
        // Retrieve the state machine manager from the global singleton
        stateMachinePtr = (void*)FUN_0043b870(DAT_01131018);
    }

    // Get the current state object via virtual function at vtable offset 0x34 (13th method)
    currentState = ((int (__thiscall*)(void*, int))(
        *(int*)(*(int*)stateMachinePtr + 0x34)))(stateMachinePtr, (int)this);

    // Check if state ID (+0x30) is 1 and if the timestamp (+0x40) is within 5000 ms of current time
    // DAT_01205224 is the global system time in milliseconds
    if (*(int*)(currentState + 0x30) != 1 ||
        *(unsigned int*)(currentState + 0x40) + 5000U <= DAT_01205224) {
        return false;
    }
    return true;
}