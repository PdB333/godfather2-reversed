// FUNC_NAME: GrowingArray::reserve
// Function address: 0x006afc10
// Role: Resize internal dynamic array to accommodate at least 'newCapacity' elements
// Each element is 8 bytes (two 4-byte fields, e.g., a pair of ints or pointers)
// Object layout:
//   +0x00: m_pData (int*) - pointer to array of elements
//   +0x04: m_nCount (int) - number of elements currently stored
//   +0x08: m_nCapacity (int) - allocated capacity (in elements)

void __thiscall GrowingArray::reserve(uint newCapacity)
{
  if (m_nCapacity < newCapacity)
  {
    // Allocate new buffer: each element is 8 bytes
    int *newData = (int *)malloc(newCapacity * 8);

    if (m_pData != 0)
    {
      // Copy existing elements (count = m_nCount)
      for (uint i = 0; i < m_nCount; i++)
      {
        newData[i * 2]     = m_pData[i * 2];     // Copy first half of element
        newData[i * 2 + 1] = m_pData[i * 2 + 1]; // Copy second half
      }
      free(m_pData);
    }

    m_pData     = newData;
    m_nCapacity = newCapacity;
  }
}