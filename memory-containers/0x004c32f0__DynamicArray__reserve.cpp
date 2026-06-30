// FUNC_NAME: DynamicArray::reserve
// Address: 0x004c32f0
// Role: Reserves capacity for a dynamic array (only grows). If new capacity > current, reallocates and copies existing elements.
// Structure fields: +0x00: m_pData (pointer to elements), +0x04: m_count (current number of elements), +0x08: m_capacity (allocated capacity)

void DynamicArray::reserve(unsigned int newCapacity)
{
    // Only grow if new capacity is larger than current capacity
    if (newCapacity > this->m_capacity)
    {
        // Allocate new buffer (each element is 4 bytes)
        int* newData = (int*)FUN_009c8e80(newCapacity * 4); // Typically operator new[] or malloc

        // If we already have data, copy existing elements
        if (this->m_pData != nullptr)
        {
            unsigned int i = 0;
            int* src = this->m_pData;
            int* dst = newData;
            // Copy up to current count (m_count)
            while (i < this->m_count)
            {
                if (newData != nullptr) // redundant check but kept as decompiled
                {
                    *dst = *src;
                }
                i++;
                src++;
                dst++;
            }
            // Free old buffer
            FUN_009c8f10(this->m_pData); // Typically operator delete[] or free
        }

        // Update pointers and capacity
        this->m_pData = newData;
        this->m_capacity = newCapacity;
    }
}