// FUNC_NAME: AudioManager::releaseAudioHandle
void __fastcall AudioManager::releaseAudioHandle(int thisPtr)
{
    // +0x110: audio handle (likely a sound slot or resource ID)
    int audioHandle = *(int *)(thisPtr + 0x110);
    if (audioHandle != -1)
    {
        // Release the audio resource via the audio system
        AudioSystem::releaseHandle(audioHandle);
        // Mark as no longer valid
        *(int *)(thisPtr + 0x110) = -1;
    }
}