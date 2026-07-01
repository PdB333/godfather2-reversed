// FUNC_NAME: AudioDataManager::releaseAudioData
void __thiscall AudioDataManager::releaseAudioData(void)
{
    // +0x7c: pointer to audio data object (AudioData*)
    // DAT_01129934: global flag indicating audio system is initialized
    if ((this->audioDataPtr != (AudioData *)0x0) && (g_bAudioSystemInitialized != 0)) {
        AudioData::release(this->audioDataPtr); // free the audio data resource
        this->audioDataPtr = (AudioData *)0x0;
    }
    return;
}