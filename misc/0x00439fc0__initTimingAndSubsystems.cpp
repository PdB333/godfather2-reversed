// FUNC_NAME: initTimingAndSubsystems
// Address: 0x00439fc0
// Role: Sets up multimedia timer high-resolution period, then calls subsystems initialization.
// Calls two internal init functions (FUN_005e38c0, FUN_004c8b30).
void initTimingAndSubsystems(void)
{
    TIMECAPS timerCaps; // TIMECAPS structure: +0x00 wPeriodMin, +0x04 wPeriodMax (total 8 bytes)
    
    timeGetDevCaps(&timerCaps, sizeof(TIMECAPS)); // Query minimum and maximum timer period
    timeBeginPeriod(timerCaps.wPeriodMin);        // Set min period for high-resolution timer
    timeGetTime();                                // Force timer start / sample (return unused)
    timeEndPeriod(timerCaps.wPeriodMin);          // Restore default period (calibration pattern)
    
    FUN_005e38c0(); // Subsystem initialization #1 (likely memory/console)
    FUN_004c8b30(); // Subsystem initialization #2 (likely input/network)
}