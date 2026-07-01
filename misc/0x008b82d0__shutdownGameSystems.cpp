// FUNC_NAME: shutdownGameSystems
// Address: 0x008b82d0
// Purpose: Called during game shutdown to release global singleton objects (e.g., input manager, audio manager).
void shutdownGameSystems(void)
{
    // Release the first global system instance (likely gInputManager)
    ReleaseSystemObject(&gInputManager);
    // Release the second global system instance (likely gAudioManager)
    ReleaseSystemObject(&gAudioManager);
}