// FUNC_NAME: shutdownAudioSystem
// Address: 0x006cc350
// Role: Cleans up audio manager resources (deinitialization)
void shutdownAudioSystem(void)
{
    // Check if audio system was initialized (global flag at 0x0112a804)
    if (g_bAudioInitialized != 0) {
        g_bAudioInitialized = 0;   // Mark as uninitialized

        // Copy current audio core data and zero out the struct
        // This likely resets a critical shared structure used by the audio engine
        AudioCoreData localCore;   // local_c, local_8, local_4
        localCore = g_audioCore;   // DAT_0112a80c
        localCore.zeroField0 = 0;
        localCore.zeroField1 = 0;
        clearAudioCoreData(&localCore, 0);   // FUN_00408a00 (memset or reset)
    }

    // Release/release resources for three global audio data objects
    releaseAudioResource(&g_audioResourceA);   // DAT_0112a814
    releaseAudioResource(&g_audioResourceB);   // DAT_0112a80c
    releaseAudioResource(&g_audioResourceC);   // DAT_0112a820
}