// FUNC_NAME: updateEarsAudioSystem
// Address: 0x005f1350
// Role: Main update loop for EA EARS audio engine. Checks initialization flags, 
//       initializes audio components if needed, then updates audio processing and resource manager.

int updateEarsAudioSystem(void)
{
    // Check if both audio system flags are set (indicating system is ready to initialize)
    if ((g_audioSystemReadyA != 0) && (g_audioSystemReadyB != 0)) {
        initializeAudioComponents();
    }

    // Process ongoing audio updates
    updateAudioProcessing();

    // Update the global audio resource manager
    updateAudioResourceManager(&g_audioResourceManager);

    return 1; // Success
}