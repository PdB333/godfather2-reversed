// FUNC_NAME: DynamicArray::reserve

void __thiscall DynamicArray::reserve(int newCapacity)
{
    // Check if we need to grow the array
    if (m_capacity >= newCapacity)
        return;

    // Allocate new block: each element is 0x2c4 bytes (708 bytes)
    int* newData = (int*)allocate(newCapacity * 0x2c4);
    if (newData == nullptr)
        return; // allocation failure – but game likely handles elsewhere

    // Copy existing elements (m_count) from old buffer to new buffer
    int* src = m_pData;
    int* dst = newData;
    for (int i = 0; i < m_count; i++)
    {
        // Copy 177 DWORDs (0x2c4 bytes) per element
        for (int j = 0; j < 0xb1; j++)
        {
            *dst++ = *src++;
        }
    }

    // Free old buffer
    deallocate(m_pData);

    // Update pointers and capacity
    m_pData = newData;
    m_capacity = newCapacity;
}