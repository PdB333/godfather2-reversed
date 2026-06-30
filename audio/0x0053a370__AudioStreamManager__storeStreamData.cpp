// FUNC_NAME: AudioStreamManager::storeStreamData
void AudioStreamManager::storeStreamData(void)
{
    // Copy 8 DWORDs (32 bytes) from the incoming buffer (this pointer) to global pending buffer
    // Global pending audio buffer at 0x0121b8e0
    g_pendingAudioBuffer[0] = *(uint32_t*)this;
    g_pendingAudioBuffer[1] = *(uint32_t*)(this + 4);
    g_pendingAudioBuffer[2] = *(uint32_t*)(this + 8);
    g_pendingAudioBuffer[3] = *(uint32_t*)(this + 12);
    g_pendingAudioBuffer[4] = *(uint32_t*)(this + 16);
    g_pendingAudioBuffer[5] = *(uint32_t*)(this + 20);
    g_pendingAudioBuffer[6] = *(uint32_t*)(this + 24);
    g_pendingAudioBuffer[7] = *(uint32_t*)(this + 28);

    // Check if current audio stream target is the base stream object and the stream state is one of the active states
    if ( (g_pAudioCurrentTarget == &g_audioStreamObject) &&
         ( (g_audioStreamState == g_audioStreamStatePlaying) ||
           (g_audioStreamState == g_audioStreamStatePaused) ||
           (g_audioStreamState == g_audioStreamStateStopped) ) )
    {
        // Submit the pending buffer to the audio stream system
        // Parameters: stream state handle, audio data pointer, size in DWORDs (8)
        audioStreamSubmitBuffer(g_audioStreamState, g_audioStreamDataPtr, &g_pendingAudioBuffer, 8);
    }
}