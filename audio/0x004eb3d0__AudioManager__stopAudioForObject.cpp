// FUNC_NAME: AudioManager::stopAudioForObject
void AudioManager::stopAudioForObject(void* object) {
    AudioManager* audioManager = GetAudioManager();  // FUN_009c8f80
    // Call virtual function at vtable offset 4 (index 1)
    (*(void (__thiscall**)(AudioManager*, void*, int))(*audioManager + 4))(audioManager, object, 0);
}