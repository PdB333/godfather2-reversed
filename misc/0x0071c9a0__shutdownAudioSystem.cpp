// FUNC_NAME: shutdownAudioSystem
// Address: 0x0071c9a0
// Role: Releases audio playback and stream objects, frees associated handles, nulls globals.

void shutdownAudioSystem(void)
{
    // Release audio playback object if exists
    if (g_pAudioPlaybackManager != (int *)0x0) {
        (**(code **)(*g_pAudioPlaybackManager + 0x10))(1); // vtable+0x10: Release(1)
    }
    // Release audio stream object if exists
    if (g_pAudioStreamManager != (int *)0x0) {
        (**(code **)(*g_pAudioStreamManager + 0x10))(1);
    }
    // Free handles (likely from EARS audio system)
    freeAudioHandle(g_hAudioHandle1);
    freeAudioHandle(g_hAudioHandle2);
    // Nullify all pointers and handles
    g_pAudioPlaybackManager = (int *)0x0;
    g_pAudioStreamManager = (int *)0x0;
    g_hAudioHandle1 = 0;
    g_hAudioHandle2 = 0;
    return;
}