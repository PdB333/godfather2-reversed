// FUNC_NAME: removeByIndex (likely member of a dynamic array class)
// Address: 0x004e14d0
// Removes element at given index from a compacted array by swapping last element into its place.
// Structure: 
// +0x00: int* m_pData (array of int32)
// +0x04: int m_count (number of elements)
void __thiscall DynamicArray::removeByIndex(int index)
{
    // If index is not the last element, copy last element into index position
    if (index != m_count - 1) {
        m_pData[index] = m_pData[m_count - 1];
    }
    // Decrement count to effectively remove the element
    m_count--;
}