// FUNC_NAME: DataBuffer::setData
// Address: 0x006a8dd0
// Thread-safe setter for an internal buffer: locks a global mutex, frees old buffer, allocates new 16-byte aligned copy.

void __thiscall DataBuffer::setData(void* data, size_t size)
{
    // Acquire global mutex (DAT_00d5d8e0)
    gMutex.lock();

    // Free existing buffer if present
    if (this->buffer_ != nullptr) {
        gMemoryManager.free(this->buffer_);
        this->buffer_ = nullptr;
        this->bufferSize_ = 0;
    }

    // Allocate new buffer with 16-byte alignment
    void* newBuf = gMemoryManager.allocateAligned(size, 0x10, 0);
    if (newBuf != nullptr) {
        this->buffer_ = newBuf;
        this->bufferSize_ = size;
        memcpy(newBuf, data, size);
    }

    // Release global mutex
    gMutex.unlock();
}