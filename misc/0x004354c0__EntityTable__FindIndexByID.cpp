// FUNC_NAME: EntityTable::FindIndexByID
int EntityTable::FindIndexByID(uint32 key, int count)
{
    int low = -1;
    int high = count;
    int mid = -1;

    while (low + 1 != high)
    {
        mid = (low + high) >> 1;
        // Compare key with the ID stored at offset 0 of the 8-byte entry
        if (key > *(uint32*)(m_entries + mid * 8))
        {
            low = mid;
        }
        else
        {
            high = mid;
        }
    }

    // Check if the final candidate matches
    if (high < count && *(uint32*)(m_entries + high * 8) == key)
    {
        return high;
    }

    return -1;
}