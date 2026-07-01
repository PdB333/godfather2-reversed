// FUNC_NAME: EntityDataManager::findEntityIndex
uint __thiscall EntityDataManager::findEntityIndex(int thisPtr, int entityId)
{
    // +0x80: low byte count (uint8)
    // +0x81: high byte count (uint8)
    // The total number of entries is the sum of these two bytes.
    uint totalCount = (uint)*(byte *)(thisPtr + 0x81) + (uint)*(byte *)(thisPtr + 0x80);
    uint index = 0;
    if (totalCount != 0)
    {
        // +0x68: pointer to array of ints (entity IDs?)
        int *array = *(int **)(thisPtr + 0x68);
        do
        {
            if (entityId == *array)
            {
                // Found: return (index >> 8) << 8 | 1
                // Low byte = 1 (found flag), upper 24 bits = index shifted right by 8.
                return (index >> 8) << 8 | 1;
            }
            index = index + 1;
            array = array + 1;
        } while (index < totalCount);
    }
    // Not found: return index & 0xFFFFFF00 (i.e., totalCount << 8 with low byte zero)
    return index & 0xFFFFFF00;
}