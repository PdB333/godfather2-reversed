// FUNC_NAME: SomeManager::synchronizedMethod
// Address: 0x006477d0
// Role: Thread-safe wrapper that acquires a critical section (stored as pointer at +0x4E8),
// calls the internal processing function (FUN_00647820), then releases the critical section.
// The lock count is maintained in the DebugInfo field of the CRITICAL_SECTION (custom EA usage).

#include <windows.h>

// Forward declaration of the internal processing function
int internalProcess(int thisPtr, int param3);

int SomeManager::synchronizedMethod(int param2, int param3) {
    // +0x4E8: pointer to a CRITICAL_SECTION (may be null)
    CRITICAL_SECTION* cs = *(CRITICAL_SECTION**)((char*)this + 0x4E8);

    if (cs != nullptr) {
        EnterCriticalSection(cs);
        // Custom lock count increment (stored in DebugInfo field as integer)
        cs->DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((intptr_t)cs->DebugInfo + 1);
    }

    int result = internalProcess((int)this, param3);

    if (cs != nullptr) {
        // Custom lock count decrement
        cs->DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((intptr_t)cs->DebugInfo - 1);
        LeaveCriticalSection(cs);
    }

    return result;
}