// FUNC_NAME: initializeGameEngine
void initializeGameEngine(void)
{
    CRITICAL_SECTION* pCS;

    // Set global initialization flag
    g_bInitialized = 1; // DAT_01222528

    // Initialize core subsystems
    initSubsystem(1);                     // FUN_00ab51e0 - likely sets up core
    initLogging();                        // FUN_00ab67c0 - maybe logging
    initStringTable(&g_stringTable, 0);   // FUN_00ab54e0 - DAT_00e2ac20
    initCriticalSection();                // FUN_006061f0 - creates critical section

    // Synchronize with critical section
    pCS = g_pCriticalSection; // DAT_011d917c
    EnterCriticalSection(pCS);
    LeaveCriticalSection(pCS);

    // Clear bit 27 (0x08000000) of state flags
    g_stateFlags = g_stateFlags & 0xF7FFFFFF; // _DAT_011d9124

    // Advance thread state if all conditions met
    if ((g_threadState == 0x3F) && (g_flagA == 0) && (g_stateFlags == 0)) {
        g_threadState = 0x40; // DAT_011d9128
    }

    // Set thread priority for group A
    g_threadPriorityA = 3; // DAT_011d8e10

    // Register message handler for ID 0xFFB
    registerMessageHandler(0xFFB, 0); // FUN_006065a0

    // Repeat synchronization
    pCS = g_pCriticalSection;
    EnterCriticalSection(pCS);
    LeaveCriticalSection(pCS);

    // Clear bit 31 (0x80000000) of state flags
    g_stateFlags = g_stateFlags & 0x7FFFFFFF;

    // Re-check state advancement
    if ((g_threadState == 0x3F) && (g_flagA == 0) && (g_stateFlags == 0)) {
        g_threadState = 0x40;
    }

    // Set thread priority for group B
    g_threadPriorityB = 3; // DAT_011d8ef0

    // Register message handler for ID 0xFFF
    registerMessageHandler(0xFFF, 0); // FUN_006065a0

    // Register a callback with a static label and function pointer
    registerStateMachine(&LAB_00618370, FUN_00618460); // FUN_00607d50

    // Clear a flag
    g_someFlag = 0; // DAT_0120595c

    // Finalize critical section usage
    finalizeCriticalSection(g_pCriticalSection); // FUN_00ab5f90

    return;
}