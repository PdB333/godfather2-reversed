// FUNC_NAME: AudioManager::initializeAudioSettings
void AudioManager::initializeAudioSettings(void)
{
    // Call a virtual method on the audio manager singleton (vtable offset 300 = 0x12C)
    // This likely applies default audio settings from g_AudioSettings
    (this->vtable[300 / sizeof(void*)])(this, &g_AudioSettings);

    // Ensure minimum volume level is at least 174 (0xAE)
    if (g_MinVolume < 174) {
        g_MinVolume = 174;
    }

    // Reset initialization flag to 0 (not yet fully initialized?)
    g_bAudioInitialized = 0;

    // Ensure maximum volume level does not exceed 174 (0xAE)
    if (174 < g_MaxVolume) {
        g_MaxVolume = 174;
    }
}