// FUNC_NAME: SomeManager::FindNextValidIndex
bool SomeManager::FindNextValidIndex(int desiredType, unsigned int* pIndex) const
{
    // Increment current index first
    unsigned int idx = *pIndex + 1;
    unsigned int count = this->m_count; // +0xA4
    if (idx >= count)
    {
        return false;
    }

    // Array of elements each 0x18 (24) bytes, first field is an int (type/handle)
    int* pArray = this->m_pArray; // +0xA0

    while (true)
    {
        int itemType = *(int*)((char*)pArray + idx * 0x18);
        // Skip null (0) and special marker (0x48) items
        if (itemType != 0 && itemType != 0x48)
        {
            // Additional check: maybe GetItemExtraType(itemType) == desiredType
            int extra = GetItemExtraType(); // FUN_007914e0
            if (extra == desiredType)
            {
                *pIndex = idx;
                return true;
            }
        }
        idx++;
        if (idx >= count)
        {
            return false;
        }
    }
}