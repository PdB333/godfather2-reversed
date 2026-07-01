// FUNC_NAME: ResourceManager::createOrReleaseResource

void ResourceManager::createOrReleaseResource(uint userData, int* pHandle, uint resourceId, uint createParams)
{
    // If the handle pointer is null, initialize the resource
    if (*pHandle == 0) {
        uint extraData = getResourceExtraData(createParams); // FUN_00540cc0
        void* tlsValue = TlsGetValue(g_allocatorTlsIndex); // Thread-local storage (discarded)
        int allocatedBlock = allocateEngineMemory(0xD0, 0x31); // size 0xD0, tag 0x31 (FUN_00aa2680)
        *(unsigned short*)(allocatedBlock + 4) = 0xD0; // Store size at offset +4 for tracking
        int newHandle = constructResource(resourceId, extraData); // FUN_009f59e0
        *pHandle = newHandle;
        if (newHandle != 0) {
            lockThreadCriticalSection(); // FUN_0043b490
            sendResourceEvent(0x2001, userData, 0); // FUN_009f01f0 – notify system
        }
        return;
    }
    // Handle already exists – release or update step
    releaseResource(resourceId); // FUN_009f5240
}