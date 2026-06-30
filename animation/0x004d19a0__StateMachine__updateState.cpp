// FUNC_NAME: StateMachine::updateState
void __thiscall StateMachine::updateState(int this) {
    int* stateData = *(int**)(this + 0x14); // +0x14: pointer to per‑state data block
    int currentState = *(int*)(stateData + 0xb0); // +0xb0: current state enum (1 = idle?, 3 = paused?)

    if (currentState == 1) {
        FUN_004d1870(); // handle state 1
        return;
    }
    if (currentState == 3) {
        FUN_004d18e0(); // handle state 3
        return;
    }

    // Default transition: set to state 6 (e.g., "transitioning" or "activating")
    *(int*)(stateData + 0xb0) = 6;
    *(int*)(stateData + 0xb8) = 0; // +0xb8: sub‑state flag / timer reset

    // Global singleton at 0x012234a8, increment transition counter at +0x90
    int* g_pGlobalSingleton = *(int**)0x012234a8; // global singleton pointer
    *(int*)(g_pGlobalSingleton + 0x90) += 1; // +0x90: pending state change count
}