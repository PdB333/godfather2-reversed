// FUNC_NAME: NetSession::sendDataProtected
// Function address: 0x006465d0
// Thread-safe wrapper: acquires critical section at +0x4E8, calls internal method, then releases.
// The DebugInfo pointer manipulation is a custom reentrancy counter.

undefined4 NetSession::sendDataProtected(int this, undefined4 param2, undefined4 param3)
{
    CRITICAL_SECTION* critSec;
    undefined4 result;

    critSec = *(CRITICAL_SECTION**)(this + 0x4E8);
    if (critSec != nullptr) {
        EnterCriticalSection(critSec);
        // Increment a reentrancy counter stored after the CRITICAL_SECTION structure
        // This is likely a custom field at critSec + 1 (sizeof CRITICAL_SECTION = 0x18? but varies)
        // Adjusts DebugInfo pointer to a value that represents increment
        // (workaround for missing atomic increment or debugging)
        critSec[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)
            ((int)&(critSec[1].DebugInfo)->Type + 1);
    }

    result = FUN_00646620(this, param2, param3); // actual method

    if (critSec != nullptr) {
        // Decrement the counter
        critSec[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)
            ((int)&critSec[1].DebugInfo[-1].SpareWORD + 1);
        LeaveCriticalSection(critSec);
    }
    return result;
}