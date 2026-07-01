// FUNC_NAME: SimpleArray::indexOf
// Function at 0x00849140: Linear search for an int value in a dynamic array.
// Class fields (offset from 'this'):
//   +0x00: int* m_pData    // pointer to array of ints
//   +0x04: int m_nCount    // number of elements in array
// Returns index if found, -1 (0xFFFFFFFF) if not found.
int __thiscall SimpleArray::indexOf(int value) const
{
    // Check if array is non-empty
    if (m_nCount == 0)
        return -1;

    int* current = m_pData;
    int index = 0;

    // Linear scan
    while (*current != value)
    {
        index++;
        current++;
        if (index >= m_nCount)
            return -1;
    }

    return index;
}