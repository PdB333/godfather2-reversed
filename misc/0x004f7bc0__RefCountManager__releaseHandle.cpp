// FUNC_NAME: RefCountManager::releaseHandle
void RefCountManager::releaseHandle(int handleIndex, void* cleanupParam)
{
    if (handleIndex == 0)
        return;

    // Retrieve per-thread data from TLS (FS segment offset 0x2c)
    ThreadLocalData* threadData = (ThreadLocalData*)__readfsdword(0x2c);
    if (threadData == nullptr)
        return;

    // Offset to the reference count array (at +0x08 from threadData, then +0x30 for base)
    int* refCount = (int*)((uint8_t*)threadData->refCountArray + 0x30 + handleIndex);

    // Decrement reference count
    (*refCount)--;

    // If count reaches zero, perform cleanup via registered callback
    if (*refCount == 0)
    {
        cleanupResource(handleIndex, cleanupParam);  // originally FUN_00519340
    }
}