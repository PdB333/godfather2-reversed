// FUNC_NAME: FloatTable::lowerBound
uint __fastcall FloatTable::lowerBound(const SortedFloatSearchContext* context)
{
    // context structure:
    // +0x4: int baseCount
    // +0x8: uint maxCount
    // +0xC: float searchValue

    uint searchCount = *(int*)(context + 4) + 2;
    uint maxCount = *(uint*)(context + 8);
    if (searchCount > maxCount)
        searchCount = maxCount;

    uint result = 0;
    uint currentIndex = g_currentIndex; // DAT_012054b4: global rotating index

    if (searchCount > 3)
    {
        do
        {
            float value = *(float*)(context + 0xC);
            float tableVal = g_floatTable[g_mask & currentIndex];
            if (value < tableVal || value == tableVal)
            {
                g_currentIndex = currentIndex + 1;
                return result;
            }
            g_currentIndex = currentIndex + 2;
            tableVal = g_floatTable[g_mask & (currentIndex + 1)];
            if (value < tableVal || value == tableVal)
            {
                return result + 1;
            }
            g_currentIndex = currentIndex + 3;
            tableVal = g_floatTable[g_mask & (currentIndex + 2)];
            if (value < tableVal || value == tableVal)
            {
                return result + 2;
            }
            currentIndex += 4;
            tableVal = g_floatTable[g_mask & g_currentIndex];
            if (value < tableVal || value == tableVal)
            {
                g_currentIndex = currentIndex;
                return result + 3;
            }
            result += 4;
            g_currentIndex = currentIndex;
        } while (result < searchCount - 3);
    }

    if (result < searchCount)
    {
        while (true)
        {
            uint maskedIndex = g_mask & g_currentIndex;
            g_currentIndex += 1;
            float value = *(float*)(context + 0xC);
            float tableVal = g_floatTable[maskedIndex];
            if (value < tableVal || value == tableVal)
                break;
            result += 1;
            if (result >= searchCount)
                return result;
        }
    }
    return result;
}