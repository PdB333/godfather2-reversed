// FUNC_NAME: StreamManager::shutdownStream

class StreamManager {
public:
    // +0xFC: Pointer to a stream handle resource (possibly an audio stream)
    void* m_pStreamHandle;

    // Internal: stop and release operations on stream slot 2
    void stopStream(int slot);        // FUN_008c5420
    void releaseStream(int slot);     // FUN_008c53a0

    // Shutdown and free the stream handle if allocated
    void shutdownStream() {
        if (m_pStreamHandle != nullptr) {
            stopStream(2);
            releaseStream(2);

            // If handle still valid, call its vtable function at offset 0x18
            // This likely releases or decrements the underlying object's reference
            if (m_pStreamHandle != nullptr) {
                (*(void(__thiscall**)(void*, int))(*(int*)m_pStreamHandle + 0x18))(m_pStreamHandle, 1);
            }

            m_pStreamHandle = nullptr;
        }
    }
};