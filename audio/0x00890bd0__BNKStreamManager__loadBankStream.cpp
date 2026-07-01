// FUNC_NAME: BNKStreamManager::loadBankStream
void __thiscall BNKStreamManager::loadBankStream(BNKStreamManager* this, int streamId)
{
    char isBusy;
    int result;
    int tmp;

    // Initialize stream loading with given ID and signature key
    registerStreamCallback(streamId);
    setStreamSignature(streamId, 0xc8f2456f);

    // Wait until stream is not busy
    isBusy = isStreamBusy();
    while (isBusy == 0) {
        yieldProcessing();
        result = checkStreamDataReady();
        if (result == 0) {
            yieldProcessing();
            tmp = getStreamData();
            tmp = convertStreamData(tmp);
            int offset = getCurrentTickOrOffset();
            // Allocate or create stream buffer at offset+0x30 (some header?)
            tmp = createStreamBuffer(tmp, offset + 0x30);
            // Store the allocated buffer pointer at +0x1C0
            this->streamBuffer = tmp;
        }
        advanceStreamState();
        isBusy = isStreamBusy();
    }

    finishStreamLoading();

    // If there is global pending data, copy it into our buffer
    if (g_globalStreamData != 0) {
        memcpy(this + 0x3C, g_globalStreamData, 0x8000); // Copy 32KB
    }

    // Call a virtual function (vtable+4) to get some object, then register callback at +0x180
    void* obj = (*(void* (*)(void*))(*(int*)(this->vtablePtr) + 4))();
    registerCallback(obj, this + 0x180);
}