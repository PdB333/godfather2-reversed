// FUNC_NAME: Engine::runGameLoop
void __thiscall Engine::runGameLoop(Engine* this)
{
    // Initialize engine
    FUN_0046c710(this);
    // Subscribe to system event with hash 0xbcab53d4 (likely "update" or "tick")
    FUN_0043aff0(this, 0xbcab53d4);
    char shouldExit = FUN_0043b120(); // Check if exit requested
    while (!shouldExit) {
        // Process next event batch
        FUN_0043b210(); // Poll/advance event system
        int eventType = FUN_0043ab70(); // Get type of current event
        if (eventType == 0) {
            // Event type 0: store data to g_lastEventData0
            int eventData = FUN_0043b210(); // Retrieve event data pointer
            g_lastEventData0 = *(int*)(eventData + 8); // +0x8: payload offset
        }
        else if (eventType == 1) {
            // Event type 1: store data to g_lastEventData1
            int eventData = FUN_0043b210(); // Retrieve event data pointer
            g_lastEventData1 = *(int*)(eventData + 8); // +0x8: payload offset
        }
        FUN_0043b1a0(); // Final step: update state after processing
        shouldExit = FUN_0043b120(); // Re-check exit condition
    }
}