//FUNC_NAME: Array::reserve
// Address: 0x005ab4a0
// Role: Ensures the internal array has capacity for at least 'newSize' elements.
//        Grows to next power of two (minimum 8) if current capacity is insufficient.
//        Uses global allocator/free functions (likely from EARS memory system).

void Array::reserve(int newSize)
{
    // Check if current capacity (at +0x50) is less than requested size
    if (m_capacity < newSize)
    {
        // Compute number of bits needed to represent (newSize - 1)
        int bits = 0;
        int temp = newSize - 1;
        while (temp != 0)
        {
            bits++;
            temp >>= 1;
        }

        // New capacity = 2^bits, but at least 8
        int newCapacity = 1 << bits;
        if (newCapacity < 8)
        {
            newCapacity = 8;
        }

        // Allocate new memory (each element is 4 bytes, second param 0 = alignment?)
        void* newData = g_allocFunc(newCapacity * 4, 0);
        memset(newData, 0, newCapacity * 4);

        // Copy existing data if present
        if (m_data != nullptr)
        {
            memcpy(newData, m_data, m_capacity * 4);
            g_freeFunc(m_data);
            m_data = nullptr;
        }

        // Update capacity and pointer
        m_capacity = newCapacity;
        m_data = newData;
    }
}