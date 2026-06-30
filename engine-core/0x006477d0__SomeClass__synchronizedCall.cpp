//FUNC_NAME: SomeClass::synchronizedCall
// Function address: 0x006477d0
// Wrapper that acquires a critical section (stored at +0x4e8), calls the internal implementation,
// then releases the lock. The critical section's DebugInfo field is used as a custom counter.

undefined4 __thiscall SomeClass::synchronizedCall(undefined4 param) {
    LPCRITICAL_SECTION criticalSection = *(LPCRITICAL_SECTION*)(this + 0x4e8); // +0x4e8: pointer to CRITICAL_SECTION
    if (criticalSection != nullptr) {
        EnterCriticalSection(criticalSection);
        // Custom lock count increment: treat DebugInfo as an integer pointer and advance it
        criticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&(criticalSection[1].DebugInfo)->Type + 1);
    }
    undefined4 result = this->internalExecute(param); // FUN_00647820
    if (criticalSection != nullptr) {
        // Custom lock count decrement: reverse the pointer adjustment
        criticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&criticalSection[1].DebugInfo[-1].SpareWORD + 1);
        LeaveCriticalSection(criticalSection);
    }
    return result;
}