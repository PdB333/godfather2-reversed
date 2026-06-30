// FUNC_NAME: gameInit

void gameInit(void)
{
    LPCRITICAL_SECTION criticalSection;

    // Set initialization flag
    g_bInitialized = 1;

    // Call various initialization subroutines
    initSubsystemA(1);
    initSubsystemB();
    initSubsystemC(&g_globalData, 0);
    initSubsystemD();

    // Acquire and release critical section to synchronize
    criticalSection = g_mainCriticalSection;
    EnterCriticalSection(g_mainCriticalSection);
    LeaveCriticalSection(criticalSection);

    // Clear bit 27 of flags (0x08000000 mask)
    g_systemFlags = g_systemFlags & 0xf7ffffff;

    // Check if system is in idle/reset state
    if ((g_stateMain == 0x3f) && (g_stateCounter == 0 && g_systemFlags == 0)) {
        g_stateMain = 0x40;
    }

    // Set mode for first subsystem
    g_subsystemMode1 = 3;
    initSubsystemE(0xffb, 0); // Register subsystem with ID 0xffb

    // Another sync point
    criticalSection = g_mainCriticalSection;
    EnterCriticalSection(g_mainCriticalSection);
    LeaveCriticalSection(criticalSection);

    // Clear bit 31 of flags (0x80000000 mask)
    g_systemFlags = g_systemFlags & 0x7fffffff;

    // Re-check idle condition
    if ((g_stateMain == 0x3f) && (g_stateCounter == 0 && g_systemFlags == 0)) {
        g_stateMain = 0x40;
    }

    // Set mode for second subsystem
    g_subsystemMode2 = 3;
    initSubsystemE(0xfff, 0); // Register subsystem with ID 0xfff

    // Register callback functions
    registerCallback(&g_callbackTable, g_callbackFunction);

    // Clear another flag
    g_bAnotherFlag = 0;

    // Final cleanup / deinitialize critical section (or release)
    cleanupCriticalSection(g_mainCriticalSection);
}