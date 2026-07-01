// FUNC_NAME: AudioDataManager::shutdown
void AudioDataManager::shutdown(void)
{
    if (g_pAudioDataManager != nullptr) {
        // Access fields at offsets +0x4 and +0x8
        // +0x4: pointer to audio resource (e.g., bank handle)
        // +0x8: reference count (uint)
        // +0xC: release flag (set to 0)
        AudioDataManager* pMgr = g_pAudioDataManager;
        ResourceHandle* pResource = reinterpret_cast<ResourceHandle*>(pMgr->m_pResource); // +0x4
        uint refCount = pMgr->m_refCount; // +0x8

        // Release the resource with its current reference count
        releaseResource(pResource, refCount);

        // Clear the resource pointer and mark as released
        pMgr->m_pResource = nullptr; // +0x4
        pMgr->m_releaseFlag = 0;      // +0xC

        // If reference count > 1, free the resource entirely
        if (refCount > 1) {
            freeResource(pResource);
        }

        // Call destructor on the manager object
        destroyObject(pMgr);

        // Null out the global singleton pointer
        g_pAudioDataManager = nullptr;
    }
}