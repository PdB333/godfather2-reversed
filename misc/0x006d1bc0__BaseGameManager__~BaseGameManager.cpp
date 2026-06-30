// FUNC_NAME: BaseGameManager::~BaseGameManager

void __thiscall BaseGameManager::~BaseGameManager() {
    // +0xD8: pointer to a dynamically allocated resource block (size 0xA0)
    int* pResource = *(int**)(this + 0xD8);

    // Set vtable to base class virtual table (prevent virtual calls during destruction)
    *(void**)this = &g_vtable_BaseGameManager;
    *(void**)(this + 8) = &g_secondaryVtable_BaseGameManager;

    // Release the allocated resource if present
    if (pResource != 0) {
        // Retrieve the global memory manager instance
        MemoryManager* pMemMgr = MemoryManager::getManager();
        // Call virtual function at offset +4 (likely free block)
        pMemMgr->freeBlock(pResource, 0xA0);
    }

    // Check global flag (e.g., whether UI system is still active)
    if (isUIActive()) {
        // Show a shutdown message of type 8 (e.g., "Saving...")
        showShutdownMessage(8);
    }

    // Perform final cleanup (e.g., flush streams, close handles)
    finalCleanup();
}