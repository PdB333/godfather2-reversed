// FUNC_NAME: AudioDataManager::shutdown
// Address: 0x006ead10
// This function appears to shut down or release the audio data manager singleton.
// It checks a flag at offset 0x78 and a handle at offset 0x60,
// calls a release function, marks the flag as done, and clears the global pointer.

// Global pointer to the audio data manager singleton
AudioDataManager* g_pAudioDataManager = nullptr;

// Forward declaration - function at 0x00408a00 (likely a resource release utility)
void releaseAudioResource(int resourceHandle, int flags);

void shutdownAudioDataManager()
{
    AudioDataManager* pManager = g_pAudioDataManager;
    if (pManager != nullptr)
    {
        // Check if the manager has not been shut down yet (flag at +0x78)
        // and if there is a valid resource handle at +0x60
        if (pManager->isShutdown == false)  // +0x78: boolean flag
        {
            int resourceHandle = pManager->resourceHandle; // +0x60: int (handle/pointer)
            if (resourceHandle != 0)
            {
                int localParams[2]; // local array for the call
                localParams[0] = resourceHandle;
                localParams[1] = 0;
                char localFlag = 0; // not used directly
                
                // Call the release function with the resource handle and flags=0
                releaseAudioResource(localParams[0], 0);
                
                // Mark the manager as shut down
                pManager->isShutdown = true; // +0x78 set to 1
            }
        }
        // Clear the global pointer
        g_pAudioDataManager = nullptr;
    }
}