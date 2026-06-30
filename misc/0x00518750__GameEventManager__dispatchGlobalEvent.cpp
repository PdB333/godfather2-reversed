// FUNC_NAME: GameEventManager::dispatchGlobalEvent

// Function address: 0x00518750
// Called from 0x00517d50 (likely mission or AI update logic)
// Uses globals from 0x012192b0, 0x012192d8, 0x012192dc (believed to be part of EARS event system)
// Arguments constructed: eventType, eventSubType, sourceEntity, and value from getEventSourceID()

void dispatchGlobalEvent(void)
{
    int eventSourceID;
    
    // Retrieve an identifier from another subsystem (e.g., player ID, AI group ID)
    eventSourceID = getEventSourceID(); // FUN_00518510
    
    // Fire a global event with the following parameters:
    // - g_pEventManager (pointer to global event system)  // +0x00
    // - g_uiEventType (type of event, e.g., 0x1234)     // +0x28
    // - g_uiEventSubType (subtype modifier)              // +0x2C
    // - 1 (likely a flag: broadcast to all listeners)
    // - 0 (priority or category)
    // - eventSourceID (the originating entity)
    // - 0 (optional data1)                               // +0x00
    // - 0 (optional data2)                               // +0x00
    fireGlobalEvent(
        DAT_012192b0,           // Pointer to event manager instance
        _DAT_012192d8,          // Event type identifier (global var)
        DAT_012192dc,           // Event subtype (global var)
        1,                      // Broadcast flag
        0,                      // Priority/queue flag
        eventSourceID,          // Source ID
        0,                      // Additional param 1
        0                       // Additional param 2
    );
}