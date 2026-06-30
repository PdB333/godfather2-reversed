// FUNC_NAME: ArrayPair::Reserve
// Address: 0x005e3000
// Purpose: Reallocate the internal dynamic array of 8-byte pairs to have at least 'newCapacity' slots.
// The class has structure:
// +0x00: int* m_pData;     // pointer to array of pairs (each pair = 8 bytes, 2 ints)
// +0x04: int m_nCount;     // number of valid elements
// +0x08: int m_nCapacity;  // allocated capacity (in elements)

void ArrayPair::Reserve(uint newCapacity)
{
    // Only grow if new capacity exceeds current capacity
    if (newCapacity > (uint)m_nCapacity)
    {
        // Allocate new buffer: each element is 8 bytes (2 ints)
        int* pNewData = (int*)operator_new(newCapacity * 8);  // FUN_009c8e80

        // Copy existing elements if any
        if (m_pData != nullptr)
        {
            uint i = 0;
            int* pDest = pNewData;
            if (m_nCount != 0)
            {
                do {
                    if (pDest != nullptr) // sanity check; should always be true
                    {
                        // Copy 8-byte pair: two consecutive ints
                        pDest[0] = m_pData[i * 2];
                        pDest[1] = m_pData[i * 2 + 1];
                    }
                    i++;
                    pDest += 2; // advance by 2 ints (8 bytes)
                } while (i < (uint)m_nCount);
            }
            // Free old buffer
            operator_delete(m_pData); // FUN_009c8f10
        }

        // Update members
        m_pData = pNewData;
        m_nCapacity = newCapacity;
    }
}