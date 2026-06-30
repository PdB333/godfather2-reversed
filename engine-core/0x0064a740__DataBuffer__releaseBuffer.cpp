// FUNC_NAME: DataBuffer::releaseBuffer
void DataBuffer::releaseBuffer(void)
{
    // If data pointer is non-null, clear the buffer and deallocate
    if (this->m_pData != nullptr) {
        uint32 i = 0;
        if (this->m_count != 0) {
            do {
                // Zero each 4-byte element in the buffer
                *(uint32*)((uint8*)this->m_pData + i * 4) = 0;
                i++;
            } while (i < this->m_count);
        }

        // If a deallocation callback is registered, call it
        if (this->m_deallocFunc != nullptr) {
            this->m_deallocFunc(
                this->m_arg,            // +0x10: context argument
                this->m_pData,          // +0x00: buffer pointer
                this->m_count * 4,      // byte size of buffer
                this->m_deallocArg      // +0x1C: additional dealloc argument
            );
        }

        // Reset buffer state
        this->m_pData = nullptr;        // +0x00
        this->m_count = 0;              // +0x04
        this->m_capacity = 0;           // +0x0C
    }
    // No return value
}