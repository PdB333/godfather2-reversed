// FUNC_NAME: TimeUtil::getRealMilliseconds
DWORD getRealMilliseconds(void)
{
    // Global state: g_timeMode = 0,1,2? 0=normal,1=profiling,2=debug?
    // g_timeFlag enables profiling
    if ((g_timeMode != 2) || (g_timeFlag == false))
    {
        DWORD ticks = GetTickCount();

        if ((g_timeMode == 1) && (g_timeFlag != false))
        {
            // Profiling slot 1 – record timestamp
            if ((g_profilingFlags & 2) == 0)
            {
                g_profilingFlags |= 2;
                g_profilingEntry1.name = "getRealMilliseconds";
                g_profilingEntry1.unknown = 0xFFFFFFFF;
                g_profilingEntry1.next = g_profilingHead;
                g_profilingHead = &g_profilingEntry1;
            }
            profilePush(&g_profilingEntry1);           // FUN_0065f6b0
            DWORD timestamp = ticks;
            recordTimestamp(0x20, &timestamp);         // FUN_0064b810
            profilePop();                               // FUN_0065fab0
        }
        return ticks;
    }

    // Mode 2: debug profiling with breakpoint limit
    if ((g_profilingFlags & 1) == 0)
    {
        g_profilingFlags |= 1;
        g_profilingEntry2.name = "getRealMilliseconds";
        g_profilingEntry2.unknown = 0xFFFFFFFF;
        g_profilingEntry2.next = g_profilingHead;
        g_profilingHead = &g_profilingEntry2;
    }
    profilePush(&g_profilingEntry2);                   // FUN_0065f6b0
    g_profileCounter++;
    if ((g_profileMaxCount != 0) && (g_profileMaxCount <= g_profileCounter))
    {
        // Trigger breakpoint
        code* breakAddr = (code*)swi(3);
        (*breakAddr)();
        return 0; // unreachable but included for completeness
    }
    DWORD result;
    retrieveTimestamp(0x20, &result);                  // FUN_0064b9e0
    // Additional check: if profiling disabled or value below threshold, return result
    if ((g_profilingDisabled == false) && (g_profilingValue < g_profilingThreshold))
    {
        return result;
    }
    // Otherwise breakpoint again
    code* breakAddr = (code*)swi(3);
    (*breakAddr)();
    return 0;
}