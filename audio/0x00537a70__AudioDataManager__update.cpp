// FUNC_NAME: AudioDataManager::update
void __cdecl AudioManager::update()
{
    // Call the underlying audio processing function with global manager and a field offset from another global
    // DAT_0121a390 is likely the singleton AudioDataManager* 
    // DAT_0121b638 is some other global object (e.g., GameManager) with a 0xc offset containing a stream identifier or handle
    AudioDataManager::processStream(g_pAudioManager, *(uint32_t*)(g_pGameManager + 0xc));
}