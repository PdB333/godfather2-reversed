// FUNC_NAME: DynamicArray::grow
void DynamicArray::grow(void)
{
    // +0x00: m_pData (int*)
    // +0x04: m_size (int)
    // +0x08: m_capacity (int)
    if (this->m_capacity < 16)
    {
        int* newData = (int*)allocate(64);          // allocate 16 elements * 4 bytes
        if (this->m_pData != 0)
        {
            for (int i = 0; i < this->m_size; i++)
            {
                if (newData != 0)
                {
                    newData[i] = this->m_pData[i];
                }
            }
            deallocate(this->m_pData);
        }
        this->m_pData = newData;
        this->m_capacity = 16;
    }
}