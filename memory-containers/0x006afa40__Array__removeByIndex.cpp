// FUNC_NAME: Array::removeByIndex
void __thiscall Array::removeByIndex(uint index)
{
    // Shift 8-byte elements left starting from index to fill the removed slot
    // m_pData (+0x00) : pointer to array of 8-byte elements
    // m_count (+0x04) : number of elements in the array
    if (index < m_count - 1)
    {
        do
        {
            uint *dst = (uint *)(m_pData + index * 8);
            uint *src = (uint *)(m_pData + (index + 1) * 8);
            *dst = *src;           // copy first 4 bytes
            dst[1] = src[1];       // copy second 4 bytes
            index++;
        } while (index < m_count - 1);
    }
    m_count--;
}