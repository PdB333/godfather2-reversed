// FUNC_NAME: IDMap::FindValueByKey
// Function address: 0x0090e070
// Role: Searches a mapping table for a key and returns its associated value.
// The class at this+0x18 holds an array of pointers to Pair structs, with count at +0x1c.
// Each Pair has key at offset +0xc and value at offset +0x4.
// Returns 0 if key not found.

int __thiscall IDMap::FindValueByKey(int thisPtr, int searchKey)
{
    int result = 0;
    unsigned int index = 0;

    uint count = *(uint *)(thisPtr + 0x1c); // +0x1c: number of entries
    if (count != 0)
    {
        int *pairPtrArray = *(int **)(thisPtr + 0x18); // +0x18: pointer to array of Pair pointers
        while (true)
        {
            int *pairPtr = (int *)pairPtrArray[index];
            int currentKey = *(int *)(pairPtr + 0x3); // +0xc (since int* offset: +0x3 -> 12 bytes)
            if (currentKey == searchKey)
            {
                break;
            }
            index++;
            if (index >= count)
            {
                return result; // 0
            }
        }
        // Found matching entry
        if (index >= 0) // always true for unsigned, but kept for safety
        {
            int *foundPair = (int *)pairPtrArray[index];
            result = *(int *)(foundPair + 0x1); // +0x4 -> value field
        }
    }
    return result;
}