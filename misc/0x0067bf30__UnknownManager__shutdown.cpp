// FUNC_NAME: UnknownManager::shutdown
void UnknownManager::shutdown(void)
{
    uint i;
    
    // Check if the manager is initialized and has objects to release
    if ((s_bInitialized != 0) && (s_objectCount != 0)) {
        i = 0;
        if (s_objectCount != 0) {
            do {
                // Release each object via a global deallocation function
                freeMemory(*(void **)(s_objectArray + i * 4));
                i = i + 1;
            } while (i < s_objectCount);
        }
        // Release the array itself
        freeMemory((void *)s_objectArray);
    }
    
    // Reset all static state
    s_objectCount = 0;
    s_objectArray = 0;
    s_bInitialized = 0;
    
    return;
}