// FUNC_NAME: GodfatherGameManager::shutdownAudioSystem
void GodfatherGameManager::shutdownAudioSystem()
{
    // g_hAudioHandle is a global handle to audio data (DAT_01129bc0)
    int* pAudioHandle = (int*)g_hAudioHandle;
    bool bHasHandle = (g_hAudioHandle != 0);

    // Clear the internal audio manager pointer (offset +0x570 in the game manager singleton at g_pGameManager)
    *(uint32_t*)((uint8_t*)g_pGameManager + 0x570) = 0;

    if (bHasHandle)
    {
        // Release any resources held by the audio system
        cleanupAudioSystem();     // FUN_006938d0
        // Free the audio handle itself
        freeAudioHandle(pAudioHandle); // FUN_009c8eb0
    }
}