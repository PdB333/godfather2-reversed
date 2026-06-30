// FUNC_NAME: SortedArray::binarySearchForKey
// Function at 0x006afa90: Binary search in a sorted array of 8-byte key-value pairs.
// Returns index of the element with matching key, or -1 if not found.
// Assumes array is sorted by the first 4 bytes (key).
int __thiscall SortedArray::binarySearchForKey(uint* keyPtr)
{
    // +0x00: mArray - pointer to array of 8-byte entries
    // +0x04: mCount - number of entries
    int* array = this->mArray;
    int count = this->mCount;
    uint searchKey = *keyPtr;

    int low = -1;
    int high = -1;
    int result = -1;

    if (count == 0)
        return -1;

    int mid = -1;
    int newMid = count;
    while (true)
    {
        mid = (newMid + low) >> 1;  // (low + high) / 2
        int tmp = mid;
        
        // Compare key with array[mid].key (first 4 bytes)
        if (*(uint*)(array + mid * 2) < searchKey)  // each element is 2 ints (8 bytes)
        {
            tmp = newMid;
            low = mid;
        }
        else
        {
            // Keep the high bound at mid
        }
        newMid = tmp;

        if (low + 1 == newMid)
            break;
    }

    // After loop, newMid is the insertion point (first element >= key)
    if (newMid < count && *(uint*)(array + newMid * 2) == searchKey)
    {
        result = newMid;
    }

    return result;
}