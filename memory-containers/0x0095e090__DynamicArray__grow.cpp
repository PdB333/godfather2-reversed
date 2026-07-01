// FUNC_NAME: DynamicArray::grow
void __thiscall DynamicArray::grow(DynamicArray* this, uint newCapacity)
{
    // Struct assumed: m_pData (+0x00), m_nCount (+0x04), m_nCapacity (+0x08)
    if (this->m_nCapacity < newCapacity)
    {
        // Allocate new block: each element is 0x20 bytes
        uint elementSize = 0x20;
        uint totalSize = newCapacity * elementSize;
        Element* newData = (Element*)alloc(totalSize); // FUN_009c8e80

        // Move existing elements to new buffer
        if (this->m_pData != nullptr)
        {
            int oldOffset = 0;
            Element* oldElem;
            Element* newElem = newData;

            for (uint i = 0; i < this->m_nCount; i++)
            {
                oldElem = (Element*)((uint8_t*)this->m_pData + oldOffset);

                // Relocate element: first detach internal handles
                if (newElem != nullptr)
                {
                    destroyElementPart(&oldElem->primary);      // FUN_004d3b50 on +0x00
                    destroyElementPart(&oldElem->secondary);    // FUN_004d3b50 on +0x04
                }

                // Call release/move functions on primary and secondary data
                if (oldElem->pSecondary != nullptr)
                {
                    oldElem->releaseSecondary(oldElem->pSecondary); // (*(code *)piVar4[7])(piVar4[4])
                }
                if (oldElem->pPrimary != nullptr)
                {
                    oldElem->releasePrimary(oldElem->pPrimary);     // (*(code *)piVar4[3])(*piVar4)
                }

                oldOffset += elementSize;
                newElem++;
            }

            // Free old memory
            free(this->m_pData); // FUN_009c8f10
        }

        // Update pointers and capacity
        this->m_pData = newData;
        this->m_nCapacity = newCapacity;
    }
}