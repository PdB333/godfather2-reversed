// FUNC_NAME: TimeManager::sleepMilliseconds

void TimeManager::sleepMilliseconds(long long milliseconds)
{
    double dMilliseconds;
    double dTemp;

    // Check if time mode is not 2 OR high precision is disabled
    if ((g_timeMode != 2) || (g_useHighPrecision == '\0')) {
        dMilliseconds = (double)milliseconds;

        // Apply scale factor if enabled
        if (g_scaleFactor != '\0') {
            dMilliseconds = dMilliseconds * g_scaleFactorDouble; // _DAT_01223368
        }

        // If time mode is 1 and high precision is enabled, log the call
        if ((g_timeMode == 1) && (g_useHighPrecision != '\0')) {
            if ((g_profilingFlags & 2) == 0) { // _DAT_01226728 bit 1 (0x2)
                g_profilingFlags |= 2; // Set bit 1
                g_currentProfileString = "getHighPrecisionMilliseconds"; // _DAT_01226710
                g_profileStringSize = 0xffffffff; // _DAT_01226714
                g_previousProfileFunction = g_currentProfileFunction; // DAT_01205a84
                g_currentProfileFunction = &g_profileStringBuffer; // DAT_01205a84 = &DAT_01226710
            }
            FUN_0065f6b0(&g_profileStringBuffer); // Enter profiling scope
            dTemp = dMilliseconds;
            FUN_0064b810(0x40, &dTemp); // Write high-precision wait time
            FUN_0065fab0(); // Exit profiling scope
        }
        return;
    }

    // Branch for time mode == 2 and high precision enabled
    if ((g_profilingFlags & 1) == 0) { // _DAT_01226728 bit 0 (0x1)
        g_profilingFlags |= 1; // Set bit 0
        g_currentProfileString = "getHighPrecisionMilliseconds"; // _DAT_0122671c
        g_profileStringSize = 0xffffffff; // _DAT_01226720
        g_previousProfileFunction = g_currentProfileFunction; // DAT_01205a84
        g_currentProfileFunction = &g_profileStringBuffer; // DAT_01205a84 = &DAT_0122671c
    }
    FUN_0065f6b0(&g_profileStringBuffer); // Enter profiling scope
    g_callCount++; // DAT_01205a80

    // Check if call count exceeded limit, trigger breakpoint
    if ((g_maxCalls != 0) && (g_maxCalls <= g_callCount)) {
        // swi(3) - software interrupt (debugger breakpoint)
        ((void (*)(void))swi(3))();
        return;
    }

    FUN_0064b9e0(0x40, &dMilliseconds); // Write millisecond wait value (different function)

    // Check if certain conditions allow early return
    if ((g_someFlag == '\0') && (g_someValue < g_threshold)) { // DAT_01127d3c, DAT_01127d38, DAT_01205a6c
        return;
    }

    // Otherwise trigger debugger breakpoint
    ((void (*)(void))swi(3))();
    return;
}