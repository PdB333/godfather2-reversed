// FUNC_NAME: Array12::removeAt
// Function address: 0x005c2a70
// Removes an element at the given index from a dynamic array of 12-byte structures.
// The array is stored as: [0] = pointer to data, [1] = count of elements.
// The element size is 0xC (12 bytes).
// The index is passed in EAX (fastcall convention).
void __fastcall Array12::removeAt(int index)
{
    // If the index is not the last element, shift subsequent elements left by one.
    if (index < m_count - 1)
    {
        int srcOffset = index * 0xC;
        do
        {
            // Copy 12 bytes from the next element to the current position.
            *(undefined8 *)(m_pData + srcOffset) = *(undefined8 *)(m_pData + 0xC + srcOffset);
            *(undefined4 *)(m_pData + srcOffset + 8) = *(undefined4 *)(m_pData + 0xC + srcOffset + 8);
            index++;
            srcOffset += 0xC;
        } while (index < m_count - 1);
    }
    // Decrement the element count.
    m_count--;
}