// FUNC_NAME: EARSStream::beginAsyncOperation
void EARSStream::beginAsyncOperation()
{
    EARSStreamObject* streamObj = *(EARSStreamObject**)(this + 0x14); // +0x14: pointer to stream object

    if (streamObj != nullptr) {
        EnterCriticalSection(&g_criticalSection); // FUN_00ab4db0

        if (streamObj->index >= 0) { // +0xa0: some index
            void* asyncHandle = AllocateAsyncHandle(); // FUN_00ac28b0
            streamObj->asyncHandle = asyncHandle; // +0xf8

            if (streamObj->state == 2) { // +0xa4: state
                if (asyncHandle != nullptr) {
                    ScheduleAsyncCallback(asyncHandle, &g_callbackData, streamObj, 0); // FUN_00ac3b80
                    LeaveCriticalSection(&g_criticalSection); // FUN_00ab4e70
                    return;
                }
            }
            else {
                if (asyncHandle != nullptr) {
                    StartAsyncRead(asyncHandle, streamObj->buffer, 0, 0, 0x20, 0, &CompletionCallback, streamObj, 0); // FUN_00ac4290
                    LeaveCriticalSection(&g_criticalSection);
                    return;
                }
                if (streamObj->refCountIndex >= 0) { // +0x9c
                    int* refCount = &g_refCountArray[streamObj->refCountIndex * 0x10 + 0x81bc]; // DAT_01223510 base
                    LOCK();
                    (*refCount)--;
                    UNLOCK();
                }
                CleanupStream(streamObj); // FUN_005ea0d0
            }
        }
        LeaveCriticalSection(&g_criticalSection);
    }
}