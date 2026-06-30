// FUNC_NAME: setAudioMasterVolume
// Function address: 0x0053a090
// Role: Store a global volume parameter and conditionally forward it to an audio device.

void __fastcall setAudioMasterVolume(int volume)
{
    // Store the volume in a global variable (likely used elsewhere)
    g_masterVolume = volume;

    // Check audio subsystem state:
    //  - g_audioSystemInstance points to a default placeholder when uninitialized
    //  - There must be more than one audio channel active
    //  - The current channel (indexed by g_audioCurrentChannelIndex) must be valid
    if (g_audioSystemInstance == &g_audioSystemDefaultPlaceholder &&
        g_audioChannelCount > 1 &&
        g_audioChannelArray[g_audioCurrentChannelIndex] != 0)
    {
        // Forward the volume to the audio device for the current channel
        AudioDeviceSetVolume(g_audioDevice,
                             g_audioChannelArray[g_audioCurrentChannelIndex],
                             volume);
    }
}