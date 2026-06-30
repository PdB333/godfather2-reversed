// FUNC_NAME: StreamedBuffer::loadFromStream
// Address: 0x00567a90
// Loads data from a stream manager into an internal buffer and reads it.

void StreamedBuffer::loadFromStream()
{
    // Flag at +0x20 indicates whether loading succeeded
    this->m_loaded = false;

    // Pointer to stream manager at +0x24
    IStreamManager* manager = *(IStreamManager**)((char*)this + 0x24);

    // Virtual function at offset 0x20 (index 8) – returns data size or readiness
    int dataSize = manager->getDataSize();

    if (dataSize > 0) {
        // Virtual function at offset 0x24 (index 9) – returns buffer pointer (argument 0)
        void* buffer = manager->getBuffer(0);

        // Store buffer at +0x8
        *(void**)((char*)this + 0x8) = buffer;

        // Mark as loaded
        this->m_loaded = true;

        // Virtual function at offset 0x30 (index 12) on the buffer object – read/seek with many arguments
        // Parameters: likely offset, origin, etc. Last parameter 0xffffffff may indicate end-of-stream.
        reinterpret_cast<IStreamBuffer*>(buffer)->read(
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xffffffff, 0
        );
    }
}