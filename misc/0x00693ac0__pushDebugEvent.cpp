// FUNC_NAME: pushDebugEvent
// Address: 0x00693ac0
// Stores an event ID (param_1) into a fixed-size buffer and calls a handler with param_2.
// The buffer holds up to 4 entries; on success returns 1, on overflow returns a masked default.

uint pushDebugEvent(uint param_1, uint param_2)
{
    // g_debugEventCount: global counter of stored events
    // g_debugEventBuffer: array of 5-dword slots (20 bytes each)
    if (g_debugEventCount < 4) {
        // Store event ID at start of the slot
        g_debugEventBuffer[g_debugEventCount * 5] = param_1;
        // Process the secondary parameter
        handleDebugEvent(param_2);
        g_debugEventCount++;
        return 1;
    }
    // Counter still increments when full (possibly allowing wraparound later?)
    g_debugEventCount++;
    // Return masked EAX (low byte cleared, likely an error code from previous operation)
    return in_EAX & 0xffffff00;
}