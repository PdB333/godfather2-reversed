// FUNC_NAME: CriticalSectionManager::leaveCriticalSectionAndGetDebugInfo
PRTL_CRITICAL_SECTION_DEBUG CriticalSectionManager::leaveCriticalSectionAndGetDebugInfo(LPCRITICAL_SECTION cs)
{
    // Update the DebugInfo pointer of the second CRITICAL_SECTION in the array (cs[1])
    // The expression computes a pointer to the byte immediately after the SpareWORD field
    // of the preceding RTL_CRITICAL_SECTION_DEBUG structure in memory.
    // This is likely a debug mechanism for tracking critical section nesting or ownership.
    cs[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((intptr_t)&cs[1].DebugInfo[-1].SpareWORD + 1);

    // Capture the updated debug info pointer before releasing the critical section
    PRTL_CRITICAL_SECTION_DEBUG pResult = cs[1].DebugInfo;

    // Leave the critical section pointed to by cs
    ::LeaveCriticalSection(cs);

    // Return the debug info pointer (used for external debugging or reference counting)
    return pResult;
}