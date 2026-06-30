// FUNC_NAME: SomeClass::synchronizedMethod
// Function at 0x00647020: Thread-safe wrapper that acquires a custom lock, calls internal method, then releases lock.
// The lock is stored at this+0x4e8 and appears to be a CRITICAL_SECTION with an adjacent reference counter
// stored in the DebugInfo field of a second CRITICAL_SECTION structure.

#include <windows.h>

class SomeClass {
public:
    // Internal method that does the actual work (at 0x00647070)
    int internalMethod(int arg3, int arg4, int arg5);

    // Synchronized wrapper
    int synchronizedMethod(int arg2, int arg3, int arg4, int arg5) {
        LPCRITICAL_SECTION lpCriticalSection = *(LPCRITICAL_SECTION*)(this + 0x4e8);
        if (lpCriticalSection != nullptr) {
            EnterCriticalSection(lpCriticalSection);
            // Custom reference count increment: treat the next CRITICAL_SECTION's DebugInfo as a counter
            // The address of the Type field of the DebugInfo structure is taken, incremented by 1, and stored back.
            lpCriticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&(lpCriticalSection[1].DebugInfo)->Type + 1);
        }
        int result = this->internalMethod(arg3, arg4, arg5);
        if (lpCriticalSection != nullptr) {
            // Custom reference count decrement: similar pointer arithmetic to restore previous value
            lpCriticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&lpCriticalSection[1].DebugInfo[-1].SpareWORD + 1);
            LeaveCriticalSection(lpCriticalSection);
        }
        return result;
    }
};