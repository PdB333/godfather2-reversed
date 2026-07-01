// FUNC_NAME: AudioDataManager::switchActiveTrack
// Function address: 0x007c69e0
// Purpose: Switches between two audio tracks (IDs 0x1d and 0x1e) based on a state flag at offset +0x118.
// Likely toggles combat vs exploration music or similar mutually exclusive audio cues.

void __thiscall AudioDataManager::switchActiveTrack(AudioDataManager* this)
{
    // +0x118: some state identifier (e.g., 1 = combat, 0 = peaceful)
    if (*(int*)((uint8_t*)this + 0x118) == 1)
    {
        // Play combat track (0x1d = 29) and stop free roam track (0x1e = 30)
        startAudioTrack(0x1d);
        stopAudioTrack(0x1e);
    }
    else
    {
        // Play free roam track (0x1e) and stop combat track (0x1d)
        startAudioTrack(0x1e);
        stopAudioTrack(0x1d);
    }
}