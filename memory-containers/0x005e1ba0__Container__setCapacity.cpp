// FUNC_NAME: Container::setCapacity
// Function address: 0x005e1ba0
// Reconstructed C++ for EA EARS engine custom container (likely integer array)
// Struct layout:
//   +0x00: int* m_pData        // pointer to element array
//   +0x04: int m_nSize        // number of elements currently stored
//   +0x08: int m_nCapacity    // allocated capacity (number of elements)

void Container::setCapacity(uint newCapacity)
{
    // Only grow if new capacity is larger than current
    if (this->m_nCapacity < newCapacity)
    {
        int* pNewData = (int*)FUN_009c8e80(newCapacity * 4); // allocate new block (4 bytes per int)
        if (this->m_pData != nullptr)
        {
            // Copy existing elements (up to current size) to new buffer
            uint i = 0;
            int* pDest = pNewData;
            if (this->m_nSize != 0)
            {
                do {
                    if (pDest != nullptr) {
                        *pDest = *(int*)(this->m_pData + i * 4);
                    }
                    i++;
                    pDest++;
                } while (i < (uint)this->m_nSize);
            }
            FUN_009c8f10(this->m_pData); // free old buffer
        }
        this->m_pData = pNewData;
        this->m_nCapacity = newCapacity;
    }
    return;
}