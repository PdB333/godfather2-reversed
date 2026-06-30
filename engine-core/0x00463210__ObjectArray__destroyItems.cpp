// FUNC_NAME: ObjectArray::destroyItems
void ObjectArray::destroyItems()
{
    // param_1 is 'this'
    // Structure at this: +0x00: m_pItems (pointer to array of elements of size 0x28)
    //                    +0x04: m_nCount (number of elements)
    // Each element (0x28 bytes): at offset +0x18: pChild (pointer to dynamically allocated sub-object)
    int count = this->m_nCount - 1;
    if (count >= 0)
    {
        int byteOffset = count * 0x28;
        do
        {
            int* pChild = *(int**)(byteOffset + 0x18 + (int)this->m_pItems);
            if (pChild != nullptr)
            {
                FUN_009c8f10(pChild); // delete pChild
            }
            count--;
            byteOffset -= 0x28;
        } while (count >= 0);
    }
    if (this->m_pItems != nullptr)
    {
        FUN_009c8f10(this->m_pItems); // delete[] m_pItems
    }
}