// FUNC_NAME: CriticalSection::leaveAndGetDebugInfo
PRTL_CRITICAL_SECTION_DEBUG CriticalSection::leaveAndGetDebugInfo(LPCRITICAL_SECTION cs)
{
    // Increment the debug info pointer by one word? Likely for tracking recursion or spin count.
    PRTL_CRITICAL_SECTION_DEBUG debugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&cs[1].DebugInfo[-1].SpareWORD + 1);
    cs[1].DebugInfo = debugInfo;
    LeaveCriticalSection(cs);
    return debugInfo;
}