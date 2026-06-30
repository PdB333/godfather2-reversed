// FUNC_NAME: StreamManager::Shutdown
void StreamManager::Shutdown(void)
{
    // Global singleton pointer to stream manager instance
    StreamManager* pStreamMgr = g_pStreamManager;  // DAT_01129878

    // Perform global initialization cleanup (possibly decrement reference count or finalize)
    StreamInitCleanup();  // FUN_0043e900

    // Retrieve pointer to managed resource at offset +0x1c
    Resource* pResource = *(Resource**)((uint8_t*)pStreamMgr + 0x1c);  // +0x1c: m_pCurrentStream

    if (pResource != nullptr)
    {
        // Release all associated sub-resources (e.g., buffer handles)
        ReleaseSubResources();  // FUN_00680f50

        // Delete the resource object itself
        DeleteResource(pResource);  // FUN_009c8eb0
    }

    // Clear the pointer to prevent dangling references
    pStreamMgr->m_pCurrentStream = nullptr;  // *(undefined4*)(pStreamMgr + 0x1c) = 0
}