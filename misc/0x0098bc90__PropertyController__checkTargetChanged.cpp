// FUNC_NAME: PropertyController::checkTargetChanged
bool __thiscall PropertyController::checkTargetChanged(void* thisPtr, undefined4 param_2) {
    int computedValue;
    int originalTarget;
    // Scope guard objects for critical section / debug scope
    int scopeGuard1[3]; // +0x00
    void (*guard1Dtor)(int*); // +0x0C
    int scopeGuard2[3]; // +0x00
    void (*guard2Dtor)(int*); // +0x0C

    // Enter debug scope or lock
    FUN_004d3bc0(param_2);
    FUN_004d3b50(scopeGuard1);
    FUN_004d5570(); // flush pending updates
    if (scopeGuard1[0] != 0) {
        guard1Dtor(scopeGuard1);
    }

    // Second scope guard
    FUN_004d3b50(scopeGuard2);
    computedValue = FUN_0098b5d0(*(int*)((int)thisPtr + 0x250), *(int*)((int)thisPtr + 0x254));
    originalTarget = *(int*)((int)thisPtr + 0x254);
    if (scopeGuard2[0] != 0) {
        guard2Dtor(scopeGuard2);
    }
    return computedValue != originalTarget;
}