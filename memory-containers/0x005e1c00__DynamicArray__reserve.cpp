// FUNC_NAME: DynamicArray::reserve
// Address: 0x005e1c00
// Role: Expands capacity of a dynamic array (grow-only). Fields: 
//   +0x00: m_pData (int*)
//   +0x04: m_nSize (uint)
//   +0x08: m_nCapacity (uint)

void DynamicArray::reserve(uint newCapacity)
{
    // If capacity already sufficient, do nothing
    if (m_nCapacity >= newCapacity)
        return;

    // Allocate new buffer (4 bytes per element)
    int* newData = (int*)FUN_009c8e80(newCapacity * 4);  // allocateMemory

    // Copy existing elements if any
    if (m_pData != nullptr)
    {
        for (uint i = 0; i < m_nSize; ++i)
        {
            newData[i] = m_pData[i];
        }
    }

    // Free old buffer
    if (m_pData != nullptr)
        FUN_009c8f10(m_pData);  // deallocateMemory

    // Update pointer and capacity
    m_pData = newData;
    m_nCapacity = newCapacity;
}