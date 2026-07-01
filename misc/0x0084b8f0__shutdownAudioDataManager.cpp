// FUNC_NAME: shutdownAudioDataManager
void __cdecl shutdownAudioDataManager(void)
{
    // If the global audio data manager instance pointer is valid, call its virtual shutdown method with flag 1
    AudioDataManager* audioDataMgr = *(AudioDataManager**)0x0112ad5c; // gAudioDataManager pointer
    if (audioDataMgr != nullptr)
    {
        // First vtable entry: virtual void shutdown(int flag)
        audioDataMgr->shutdown(1);
    }
    // Shutdown the stream manager (global instance at 0x0112dd08)
    StreamManager* streamMgr = (StreamManager*)0x0112dd08;
    // Call to FUN_00408310: likely StreamManager::shutdown or similar
    StreamManager::shutdown(streamMgr);
}