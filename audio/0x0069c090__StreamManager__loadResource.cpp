// FUNC_NAME: StreamManager::loadResource
void StreamManager::loadResource(void *this, char *identifier)
{
    int flag;
    void *handle;
    // Stack-based RAII handles with destructor function pointers
    struct HandleStruct {
        void *object;
        void *destructor; // +0x00? Actually decompiled shows local_20[3] then code* local_14; likely struct has 3 fields
    } handle1, handle2;
    // Actually the decompiled local arrays are ambiguous, but we treat them as 12-byte structures
    
    this->lock(); // FUN_004d3bc0
    flag = isStreamingEnabled(); // FUN_00699ff0
    if (flag == 0) {
        // Synchronous path? or streaming disabled
        if (g_maxStreamHandles < 0) return; // DAT_00e506ac
        int slotCount = (g_streamHandleArrayEnd - g_streamHandleArrayBegin) >> 2;
        if (slotCount <= g_maxStreamHandles) return;
        this->lock();
        loadAsync(&handle1, identifier); // FUN_0069b5a0
    } else {
        // Asynchronous path
        this->lock();
        handle = loadSynchronous(&handle2, identifier); // FUN_006985a0
        releaseAsync(&handle1); // FUN_0069b380
        this->releaseMemory(handle); // FUN_004d3e20
        if (handle2.object) {
            handle2.destructor(handle2.object); // local_4
        }
    }
    if (handle1.object) {
        handle1.destructor(handle1.object); // local_14
    }
    return;
}