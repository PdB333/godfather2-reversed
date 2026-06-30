// FUNC_NAME: StreamBuffer::commitPendingTransfer
class SomeObject {
public:
    virtual int getTransferData(void* output) = 0; // vtable+4
};

class BufferObject {
public:
    virtual void releaseBuffer(int param1, int param2) = 0; // vtable+4
};

struct SharedStruct {
    SomeObject* m_pSource;  // +0x00
    BufferObject* m_pBuffer; // +0x04
    int m_size;              // +0x08
};

class StreamBuffer {
public:
    int m_currentSize;       // +0x08
    int m_pendingSize;       // +0x0c
    void* m_pBuffer;         // +0x10
    int m_result;            // +0x14
    SharedStruct* m_pShared; // +0x18

    void commitPendingTransfer();
};

void StreamBuffer::commitPendingTransfer()
{
    // Save original state
    int savedCurrentSize = this->m_currentSize;  // +0x08
    int savedPendingSize = this->m_pendingSize;  // +0x0c
    void* savedBuffer = this->m_pBuffer;         // +0x10
    SharedStruct* shared = this->m_pShared;      // +0x18

    // Clear current size and buffer
    this->m_currentSize = 0;
    this->m_pBuffer = 0;

    // Extract shared pending buffer info
    BufferObject* pendingBuffer = shared->m_pBuffer; // +0x04
    int pendingSize = shared->m_size;                // +0x08

    // Call virtual method on source (likely fetching transfer ready state)
    char transferOutput[4];
    this->m_result = shared->m_pSource->getTransferData(transferOutput);

    if (savedPendingSize != 0)
    {
        // If there was pending size, adopt the pending buffer and keep its size
        this->m_currentSize = savedPendingSize;
        this->m_pBuffer = pendingBuffer;
        return;
    }

    if (savedBuffer != 0)
    {
        // Otherwise release the old buffer through the pending buffer object
        pendingBuffer->releaseBuffer((int)savedBuffer, 0);
    }
}