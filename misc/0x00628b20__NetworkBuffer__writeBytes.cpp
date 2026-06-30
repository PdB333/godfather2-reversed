// FUNC_NAME: NetworkBuffer::writeBytes
void NetworkBuffer::writeBytes(const char* src, int length)
{
    if (length == 0) return;

    do {
        length--;

        // Check if buffer is full (write pointer reached end of 0x20C-byte buffer).
        // Buffer layout (offsets relative to this):
        // +0x00: m_writePtr (char* current write position)
        // +0x04: m_flushCount (int, number of packet flushes)
        // +0x08: m_stream (void* to a stream/connection object)
        // +0x0C: data buffer start (0x200 bytes capacity)
        if ((char*)this + 0x20C <= this->m_writePtr)
        {
            int dataSize = this->m_writePtr - (char*)(this + 3); // bytes written in data area
            if (dataSize != 0)
            {
                Stream* stream = this->m_stream;

                // Check stream state (e.g., send buffer has space)
                if (*(uint*)(*(int*)(stream + 0x10) + 0x20) <=
                    *(uint*)(*(int*)(stream + 0x10) + 0x24))
                {
                    uint timestamp = getTimestamp();      // 0x00627290
                    prepareFlush(stream, 0);               // 0x00626f80
                    flushPart(0);                          // 0x00626fd0
                    prepareFlush(stream, 0);               // 0x00626f80
                    setFlushTimestamp(timestamp);          // 0x00627010
                    finalizeFlush();                       // 0x006270e0
                }

                // Write packet header: type 4 and encoded size
                uint* packetOut = *(uint**)(stream + 8); // output pointer in stream
                *packetOut = 4;                           // packet type
                packetOut[1] = encodeData(stream, (char*)(this + 3), dataSize); // 0x00638920
                *(int*)(stream + 8) += 8;                 // advance stream output pointer

                this->m_flushCount++;
                this->m_writePtr = (char*)(this + 3);     // reset to start of data area

                notifyFlushDone();                        // 0x006289a0
            }
        }

        // Write one byte from source to buffer
        *this->m_writePtr = *src;
        this->m_writePtr++;
        src++;
    } while (length != 0);
}