// FUNC_NAME: AudioStreamManager::stopStreams
void AudioStreamManager::stopStreams(void)
{
    // Stop first audio stream (e.g., background music) if active
    if (gAudioStreams[0] != 0) {
        stopStream();
    }
    // Stop second audio stream (e.g., ambient) if active
    if (gAudioStreams[1] != 0) {
        stopStream();
    }
}