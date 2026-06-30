// FUNC_NAME: AudioManager::playVoiceEffect
void AudioManager::playVoiceEffect(uint soundId) // soundId passed in ESI
{
    // Global state assignments
    g_currentVoiceId = soundId;

    // Determine which audio context is active and prepare if needed
    if (g_activeAudioContext == g_musicContextId) {
        if (g_musicContextIsReady != 0) {
            AudioManager::prepareAudioContext(); // 0x006063b0
        }
        iVar2 = g_musicContextData; // 0x01125b84
    } else {
        if (g_speechContextIsReady != 0) {
            AudioManager::prepareAudioContext(); // 0x006063b0
        }
        iVar2 = g_speechContextData; // 0x01125b88
    }

    if (iVar2 != 0) {
        // Initialize position to zero
        float position[2] = { 0.0f, 0.0f };

        // Look up sound descriptor from global array
        SoundDescriptor* desc = nullptr;
        if (soundId < 0x1000) {
            desc = &g_soundDescriptors[soundId]; // stride 0x38
        } else {
            desc = nullptr;
        }

        // Compute pitch and sample rate factors
        float pitchFactor = g_baseFrequency / (float)desc->pitch;          // offset +2
        float sampleRateFactor = g_baseFrequency / (float)desc->sampleRate; // offset +4

        // Play the voice with the selected context
        AudioManager::playVoice(g_activeAudioContext, iVar2, &position); // 0x0060add0
    }
}