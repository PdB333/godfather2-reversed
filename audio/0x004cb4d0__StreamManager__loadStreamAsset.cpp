// FUNC_NAME: StreamManager::loadStreamAsset
bool StreamManager::loadStreamAsset()
{
    // Check if the stream handle (pointer at +0x8) is already allocated
    if (this->streamHandle != nullptr) // +0x8: pointer to stream resource
    {
        // Perform global streaming state update (e.g., prepare for load)
        g_streamManager_submitLoadRequest(); // 0x005dbdf0

        // Query if the global streaming engine has finished loading the bank
        if (g_isStreamBankLoaded(g_streamBankGlobal)) // 0x005ddc30, DAT_01223508
        {
            // Mark this stream object as ready/active
            this->isReady = true; // +0x18: byte flag (1 = ready)
            return true;
        }
    }
    return false;
}