// FUNC_NAME: DebugCounter::increment
// Function address: 0x00643ed0
// Increments a debug info pointer (used as a reference counter) under a critical section.
PRTL_CRITICAL_SECTION_DEBUG DebugCounter::increment() {
    // 'this' is passed in ESI register, mapped to unaff_ESI by Ghidra.
    // The first member is a CRITICAL_SECTION (sizeof = 0x18)
    // At offset 0x18 is a PRTL_CRITICAL_SECTION_DEBUG counter.
    EnterCriticalSection(reinterpret_cast<LPCRITICAL_SECTION>(this));
    // Increment the counter pointer by 1 (treating it as an integer)
    m_debugInfo = reinterpret_cast<PRTL_CRITICAL_SECTION_DEBUG>(
        reinterpret_cast<int>(m_debugInfo) + 1
    );
    return m_debugInfo;
}