// FUNC_NAME: SimpleArray::reserve
// Function address: 0x005fa9a0
// Role: Resize dynamic array (increase capacity) - copies existing elements and frees old buffer
// Structure layout (offset from this):
// +0x00 m_pBuffer (unsigned int*): pointer to allocated element array
// +0x04 m_count (unsigned int): number of currently stored elements
// +0x08 m_capacity (unsigned int): allocated capacity (max elements)

void __thiscall SimpleArray::reserve(unsigned int newCapacity)
{
    if (this->m_capacity < newCapacity)
    {
        unsigned int* newBuffer = (unsigned int*)FUN_009c8e80(newCapacity * sizeof(unsigned int)); // allocate new buffer
        if (this->m_pBuffer != 0)
        {
            unsigned int i = 0;
            unsigned int* dest = newBuffer;
            unsigned int count = this->m_count;
            if (count != 0)
            {
                do
                {
                    if (dest != 0)
                    {
                        *dest = *(unsigned int*)(this->m_pBuffer + i);
                    }
                    i = i + 1;
                    dest = dest + 1;
                } while (i < count);
            }
            FUN_009c8f10(this->m_pBuffer); // free old buffer
        }
        this->m_pBuffer = newBuffer;
        this->m_capacity = newCapacity;
    }
}