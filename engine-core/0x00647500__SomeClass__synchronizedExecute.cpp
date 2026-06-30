// FUNC_NAME: SomeClass::synchronizedExecute
// 0x00647500 - Thread-safe wrapper with custom lock counter tracking
// This function locks a critical section (offset +0x4e8) before calling the inner
// function FUN_00647550(param3), then unlocks. The debug info manipulation is a
// custom depth/refcount mechanism on the critical section structure.

int SomeClass::synchronizedExecute(int param1, int param2, int param3) {
    // Critical section pointer stored at offset 0x4e8 from this
    CRITICAL_SECTION *cs = *(CRITICAL_SECTION **)((uint8_t *)this + 0x4e8);

    if (cs != nullptr) {
        EnterCriticalSection(cs);

        // Custom increment of a lock counter stored in the debug info area
        // This likely tracks nested lock depth or thread ID
        cs[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&(cs[1].DebugInfo->Type) + 1);
    }

    // Call the actual implementation (FUN_00647550), only param3 is passed
    int result = FUN_00647550(param3);  // Typically this would be a member method

    if (cs != nullptr) {
        // Custom decrement of the lock counter
        cs[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&cs[1].DebugInfo[-1].SpareWORD + 1);

        LeaveCriticalSection(cs);
    }

    return result;
}