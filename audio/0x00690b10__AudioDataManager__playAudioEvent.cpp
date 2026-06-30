// FUNC_NAME: AudioDataManager::playAudioEvent
void AudioDataManager::playAudioEvent(int audioEventId)
{
    if (gAudioDataManager != 0) {
        int* pInitialized = *(int**)(gAudioDataManager + 4); // +0x4: pointer to initialization flag
        // If the audio system is ready, play immediately and return.
        // Otherwise, still queue or play after initialization.
        if (pInitialized != 0 && *pInitialized != 0) {
            int resourceHandle = resolveResource(audioEventId);
            playResource(resourceHandle);
            return;
        }
        int resourceHandle = resolveResource(audioEventId);
        playResource(resourceHandle);
    }
}