// FUNC_NAME: deinitializeAudioSubsystem
void deinitializeAudioSubsystem(void)
{
    // Global flag indicating whether the audio subsystem is active (DAT_0112a808)
    // Global handle/identifier for the subsystem (DAT_0112a820)
    if (g_audioSubsystemActive != 0) {
        uint32_t audioHandle = g_audioSubsystemHandle;
        uint32_t reserved = 0;
        uint8_t flags = 0;

        // Call internal shutdown routine for the audio subsystem
        // param_2 = 0 indicates full teardown
        FUN_00408a00(&audioHandle, 0);

        // Mark subsystem as inactive
        g_audioSubsystemActive = 0;
    }
}