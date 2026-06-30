// FUNC_NAME: CRangeManager::GetNthContaining
int __thiscall CRangeManager::GetNthContaining(int value, int n)
{
    // +0x38: number of entries in the range array
    int count = *(int*)((char*)this + 0x38);
    if (count <= 0)
        return 0;

    // +0x18: pointer to array of 12-byte entries (each: min, max, dataPointer?)
    int* entryBase = *(int**)((char*)this + 0x18);

    for (int i = 0; i < count; i++)
    {
        // Each entry is 3 ints (12 bytes): entry[0]=min, entry[1]=max, entry[2]=(unused in loop)
        int* entry = entryBase + i * 3;

        // Check if value is within [min, max)
        if (value < entry[0])      // value < min -> stop search
            return 0;
        if (value < entry[1])      // value < max -> this range contains value
        {
            n--;
            if (n == 0)
            {
                // Return data pointer: the first int of the entry is a base address, add 0x10 offset
                return entry[0] + 0x10;
            }
        }
    }
    return 0;
}