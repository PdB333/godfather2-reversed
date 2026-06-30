// FUNC_NAME: GameManager::cleanupResources

void __thiscall GameManager::cleanupResources() {
    // Offset +0x211c: flag indicating whether a stream/resource is active
    if (m_bActiveFlag) {
        // Unload/stop the active resource
        FUN_004df600(); // e.g., stopStream() or releaseHandle()
        m_bActiveFlag = false;
    }

    // Offset +0x2120: pointer to a resource object (e.g., stream handle)
    int* pResource = m_pResourcePtr;
    if (pResource) {
        // Pre-cleanup step (e.g., flush or detach)
        FUN_0090c670(); // e.g., flushCache() or detachListener()
        // Delete the resource object
        FUN_009c8eb0(pResource); // e.g., operator delete or freeResource()
        m_pResourcePtr = nullptr;
    }
}