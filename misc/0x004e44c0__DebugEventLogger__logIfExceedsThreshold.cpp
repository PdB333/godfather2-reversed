// FUNC_NAME: DebugEventLogger::logIfExceedsThreshold
// Address: 0x004e44c0
// Checks if a debug event's time/value exceeds a global threshold, and if so, logs it.
void __thiscall DebugEventLogger::logIfExceedsThreshold(int this, int arg2, int arg3)
{
    uint32_t* eventData; // pointer passed in EAX (compiler optimization)

    // Global threshold for logging (e.g., max delta time)
    extern float g_debugEventThreshold; // DAT_00e2af44

    if (g_debugEventThreshold < static_cast<float>(eventData[3]))
    {
        // Log the event: pass event ID, two other fields, the value, and the original arguments
        FUN_0052fc90(eventData[0], eventData[1], eventData[2], eventData[3], arg2, arg3, this);
    }
    return;
}