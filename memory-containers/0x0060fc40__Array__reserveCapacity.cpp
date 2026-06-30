// FUNC_NAME: Array::reserveCapacity

void Array::reserveCapacity(uint newCapacity)
{
    // +0x00: m_data (pointer to array)
    // +0x04: m_size (number of elements)
    // +0x08: m_capacity (maximum number of elements)
    if (m_capacity < newCapacity)
    {
        // Allocate new buffer: each element is 16 bytes
        uint8* newBuffer = (uint8*)allocateMemory(newCapacity * 0x10);
        if (m_data != nullptr)
        {
            // Copy existing elements (16 bytes each)
            for (uint i = 0; i < m_size; ++i)
            {
                *(uint64*)(newBuffer + i * 0x10) = *(uint64*)(m_data + i * 0x10);
                *(uint64*)(newBuffer + i * 0x10 + 8) = *(uint64*)(m_data + i * 0x10 + 8);
            }
        }
        // Free old buffer
        if (m_data != nullptr)
        {
            freeMemory(m_data);
        }
        m_data = newBuffer;
        m_capacity = newCapacity;
    }
}