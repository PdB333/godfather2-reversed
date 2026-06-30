// FUN_NAME: StreamLoader::processAsyncOperation
void StreamLoader::processAsyncOperation() {
    void* pStream = *(void**)((int)this + 0x14); // +0x14: m_pStream (IStream*)
    if (pStream == nullptr) {
        return;
    }

    GlobalMutexLock(&DAT_00e2e4c8); // Lock global mutex (0x00e2e4c8)

    if (*(int*)((int)this + 0x170) == 2) { // m_state == STATE_READY (2)
        uint32_t requestHandle = AsyncRequestManager::createRequest(); // FUN_00ac28b0
        *(uint32_t*)((int)this + 0x1c8) = requestHandle; // m_requestHandle
        AsyncRequestManager::setCompletionCallback(requestHandle, &StreamLoader::onStreamReady, (int)this, 0); // FUN_00ac3b80, callback at 0x00458080
        GlobalMutexUnlock(); // FUN_00ab4e70
        return;
    }

    uint32_t requestHandle = AsyncRequestManager::createRequest(); // FUN_00ac28b0
    *(uint32_t*)((int)this + 0x1c8) = requestHandle; // m_requestHandle

    if (requestHandle != 0) {
        void* pData = *(void**)((int)this + 0x16c); // m_pData (allocated buffer)
        if (pData != nullptr) {
            uint32_t dataSize = *(uint32_t*)((int)this + 0x168); // m_dataSize
            GlobalMutexUnlock(); // FUN_00ab4e70 (temporary unlock? Or separate unlock function?)

            // Wait until async request completes (polling with sleep)
            while (IsRequestCompleted(dataSize) == '\0') { // FUN_00c9eb10
                uint32_t sleepMs = 1;
                Sleep(&sleepMs); // FUN_00ab4b40
            }

            // Reset buffer state
            pData = nullptr; // iVar3 = 0
            GlobalMutexLock(&DAT_00e2e4c8); // Lock again
            *(void**)((int)this + 0x16c) = pData; // m_pData = nullptr
            *(uint32_t*)((int)this + 0x164) = 0; // m_currentOffset
            *(uint32_t*)((int)this + 0x168) = 0; // m_dataSize

            if (*(int*)((int)this + 0x170) == 2) { // m_state == STATE_READY
                AsyncRequestManager::setCompletionCallback(requestHandle, &StreamLoader::onStreamReady, (int)this, 0);
                GlobalMutexUnlock();
                return;
            }
        }

        // Initiate async read from stream into local buffer at +0x1e0 (32 bytes)
        AsyncRequestManager::read(requestHandle, (int)this + 0x1e0, 0, 0, 0x20, 0, &StreamLoader::onReadComplete, (int)this, 0); // FUN_00ac4290, callback at 0x00457e60
        GlobalMutexUnlock();
        return;
    }

    // Error: request handle is null
    *(uint8_t*)((int)this + 0x200) = 1; // m_errorFlag
    *(uint32_t*)((int)this + 0x13c) = 0; // m_callbackContext
    if (*(void**)((int)this + 0x138) != nullptr) { // m_callback
        *(uint8_t*)(*(void**)((int)this + 0x138)) = 0; // Invalidate callback
    }
    *(int*)((int)this + 0x170) = 0; // m_state = STATE_IDLE
    GlobalMutexUnlock();
}