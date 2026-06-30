// FUNC_NAME: TNLConnection::addDataToSendBuffer

// Send buffer descriptor (pointed to by this+0x10)
struct SendBuffer {
    uint32_t flushThreshold; // +0x20: when currentSize >= this threshold, flush
    uint32_t currentSize;    // +0x24: number of bytes currently queued
};

void TNLConnection::addDataToSendBuffer(void *data)
{
    // Get the send buffer descriptor
    SendBuffer *buffer = *(SendBuffer **)((char *)this + 0x10);
    
    // If the buffer has reached the flush threshold, send it out
    if (buffer->currentSize >= buffer->flushThreshold)
    {
        this->flushSendBuffer(); // FUN_00627360
    }
    
    // Queue the new data to the outgoing stream
    this->appendToSendStream(data); // FUN_00636910
}