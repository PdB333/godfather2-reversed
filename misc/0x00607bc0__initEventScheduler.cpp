// FUNC_NAME: initEventScheduler
int initEventScheduler(void)
{
    // Reset a global flag (e.g., force update)
    g_flagByte = 0;  // +0x1205759

    // Call initialization subroutine
    initSomething();

    // Build a timer/event structure from a global constant
    struct TimerEvent {
        DWORD field_0;  // offset 0
        DWORD field_4;  // offset 4
        DWORD field_8;  // offset 8
    } timer;

    timer.field_0 = g_nullGuid;  // DAT_00e2b1a4
    timer.field_4 = g_nullGuid;  // DAT_00e2b1a4
    timer.field_8 = 0;

    // Register the timer event
    registerTimerEvent(&timer);

    return 0;
}