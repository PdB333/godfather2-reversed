// FUNC_NAME: shutdownMemoryPools
void shutdownMemoryPools(void)
{
    int* poolPtr1;
    int* poolPtr2;

    // Shutdown first memory pool (size 0x1DD0)
    if (g_pool1Ptr != 0) {
        cleanupPool1();
        poolPtr1 = (int*)getMemoryManager();
        // Call virtual release function at vtable+4 (likely MemoryManager::free)
        (**(code**)(*poolPtr1 + 4))(g_pool1Ptr, 0x1dd0);
        g_pool1Ptr = 0;
    }

    // Shutdown second memory pool (size 0x2E50)
    if (g_pool2Ptr != 0) {
        cleanupPool2();
        poolPtr2 = (int*)getMemoryManager();
        (**(code**)(*poolPtr2 + 4))(g_pool2Ptr, 0x2e50);
        g_pool2Ptr = 0;
    }

    // Clear global flag and final cleanup
    g_shutdownFlag = 0;
    finalCleanup();
}