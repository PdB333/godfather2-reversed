// FUNC_NAME: KeyedArray::binarySearchKey
int __thiscall KeyedArray::binarySearchKey(const uint& key) const
{
    // this[0] = pointer to array of 16-byte elements, first uint is key
    // this[1] = count of elements
    int* arrayPtr = (int*)this[0];
    int count = this[1];
    int low = -1;
    int high = count;

    int foundIndex = -1;

    // Binary search: find the first index where key >= searched key
    while (low + 1 != high)
    {
        int mid = (high + low) >> 1;
        int newHigh = mid;
        if (*(uint*)(mid * 0x10 + (int)arrayPtr) < key)
        {
            newHigh = high;
        }
        low = mid;
        high = newHigh;
    }

    // Verify if exact match
    if (high < count && *(uint*)(high * 0x10 + (int)arrayPtr) == key)
    {
        foundIndex = high;
    }

    return foundIndex;
}