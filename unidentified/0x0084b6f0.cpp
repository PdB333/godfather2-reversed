// Function address: 0x0084b6f0
// Role: Static initialization of the global AudioDataManager instance
// Calls AudioDataManager::Initialize on the global instance.

extern AudioDataManager g_AudioDataManagerInstance;

void initializeAudioDataManager(void)
{
    AudioDataManager::Initialize(&g_AudioDataManagerInstance);
}