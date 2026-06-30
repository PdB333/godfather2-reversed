// FUNC_NAME: StreamManager::readLocked
// Address: 0x006465d0
// Role: Thread‑safe wrapper that acquires a critical section stored at +0x4e8,
// calls the internal read function (0x646620), then releases the critical section.
// The code also uses the DebugInfo field of an adjacent CRITICAL_SECTION as a
// custom reentrancy counter.

#include <windows.h>

// Forward declaration of the actual read function (defined at 0x00646620)
uint32_t __thiscall StreamManager::readInternal(uint32_t param1, uint32_t param2);

uint32_t __thiscall StreamManager::readLocked(uint32_t arg1, uint32_t arg2)
{
    // +0x4e8: pointer to a CRITICAL_SECTION used for mutex
    CRITICAL_SECTION *cs = *(CRITICAL_SECTION **)((uint8_t *)this + 0x4e8);

    if (cs != nullptr)
    {
        EnterCriticalSection(cs);
        // Increment the custom reentrancy counter in the DebugInfo field
        // of the second CRITICAL_SECTION (adjacent in memory)
        cs[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)
            ((int)&(cs[1].DebugInfo)->Type + 1);
    }

    uint32_t result = this->readInternal(arg1, arg2);  // actual work at 0x646620

    if (cs != nullptr)
    {
        // Decrement the custom reentrancy counter
        cs[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)
            ((int)&cs[1].DebugInfo[-1].SpareWORD + 1);
        LeaveCriticalSection(cs);
    }

    return result;
}