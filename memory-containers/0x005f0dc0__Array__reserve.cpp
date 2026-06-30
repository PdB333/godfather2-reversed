// FUNC_NAME: Array::reserve
void Array::reserve(uint32_t newCapacity) {
    if (m_capacity < newCapacity) {
        int* newData = (int*)allocateMemory(newCapacity * 4);
        if (m_pData != 0) {
            uint32_t i = 0;
            int* dest = newData;
            if (m_count != 0) {
                do {
                    if (dest != 0) {
                        *dest = *(int*)(m_pData + i);
                    }
                    i++;
                    dest++;
                } while (i < m_count);
            }
            deallocateMemory(m_pData);
        }
        m_pData = newData;
        m_capacity = newCapacity;
    }
}