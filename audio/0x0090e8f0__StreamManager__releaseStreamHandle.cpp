// FUNC_NAME: StreamManager::releaseStreamHandle

class StreamManager {
public:
    // +0xB8: m_streamHandle (handle to an active stream, -1 if none)
    int m_streamHandle;

    // releases a stream handle (likely a BNK or audio stream)
    void releaseStreamHandle() {
        if (m_streamHandle != -1) {
            internalReleaseHandle(m_streamHandle);
            m_streamHandle = -1;
        }
    }

private:
    // internal function to free the stream resource
    void internalReleaseHandle(int handle);
};