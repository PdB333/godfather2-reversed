// FUNC_NAME: AudioManager::setCurrentAudioId
void __fastcall AudioManager::setCurrentAudioId(int audioId)
{
    // Store the new audio ID (e.g., a context or command identifier)
    AudioManager::s_CurrentAudioId = audioId;

    // Validate the singleton pointer is initialized (points to static storage)
    // and the manager is active, and the current playback slot is occupied.
    if ((AudioManager::s_SingletonPtr == &AudioManager::s_SingletonStorage) &&
        (AudioManager::s_IsActive != 0) &&
        (AudioManager::s_AudioPlaybackArray[AudioManager::s_CurrentAudioIndex] != nullptr))
    {
        // Forward the audio ID to the playback system for the selected slot.
        AudioManager::applyAudioToPlayback(
            AudioManager::s_AudioContext,
            AudioManager::s_AudioPlaybackArray[AudioManager::s_CurrentAudioIndex],
            audioId);
    }
}