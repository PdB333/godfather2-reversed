// FUNC_NAME: DynamicArray::reserve (0x006aa370) - Ensure capacity for dynamic array, reallocate if needed
void __thiscall DynamicArray::reserve(uint newCapacity) {
    int* newData;
    uint i;

    // If current capacity is insufficient, allocate new block and copy existing elements
    if (m_nCapacity < newCapacity) {
        // Allocate memory for newCapacity elements (each 4 bytes)
        newData = (int*)allocate(newCapacity * 4);
        if (m_pData != 0) {
            i = 0;
            // Copy all existing elements from old buffer to new (up to current size)
            while (i < m_nSize) {
                newData[i] = m_pData[i];
                i++;
            }
            // Free old buffer
            deallocate(m_pData);
        }
        // Update pointer and capacity, size remains unchanged
        m_pData = newData;
        m_nCapacity = newCapacity;
    }
}