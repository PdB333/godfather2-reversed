// FUNC_NAME: registerInitialEventCallback
// Address: 0x009909b0
// Registers a callback for a game event and finalizes the registration process.

void registerInitialEventCallback(void)
{
    // Register the callback function at LAB_009907f0 for the event identifier at DAT_01130938.
    // The event manager singleton is at DAT_00e3e658.
    registerEventCallback(&g_eventManager, &g_eventIdentifier, 0, &onGameEvent, 0, 0);

    // Finalize the event registration (e.g., apply pending registrations).
    finalizeEventRegistration();
}