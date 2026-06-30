// FUNC_NAME: StreamManager::releaseStream
int StreamManager::releaseStream() {
    // +0x1c8 : int m_streamHandle
    if (this->m_streamHandle >= 0) {
        // DAT_01223510 is a global pointer to StreamManager singleton or similar
        // Call a function via vtable at offset 0x54 (likely isStreamValid or checkHandle)
        bool isValid = (*(bool (__thiscall **)(int))(*(int *)DAT_01223510 + 0x54))(this->m_streamHandle);
        if (isValid) {
            this->m_streamHandle = -1;
            if (this->m_streamData != nullptr) {
                // +0x1c0 : void* m_streamData
                // DAT_01223518 points to a memory manager, offset +4 is its vtable for freeing
                void* memoryMgr = *(void**)(DAT_01223518 + 4);
                if (memoryMgr != nullptr) {
                    (*(void (__thiscall **)(void*, void*, int))(*(int*)memoryMgr + 4))(memoryMgr, this->m_streamData, 0);
                }
                this->m_streamData = nullptr;
                this->m_streamDataSize = 0;  // +0x1c4
                return 1;
            }
        }
    }
    return 0;
}