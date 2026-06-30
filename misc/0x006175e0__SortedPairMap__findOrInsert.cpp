// FUNC_NAME: SortedPairMap::findOrInsert
uint* __thiscall SortedPairMap::findOrInsert(uint* thisPtr, uint* keyPtr, uint* valuePtr)
// +0x00: pointer to array of key-value pairs (each 2 uints)
// +0x04: count of pairs in array
{
    int index = 0;
    int count = thisPtr[1]; // number of existing pairs

    if (count > 0)
    {
        uint* baseArray = (uint*)thisPtr[0]; // pointer to first pair

        do
        {
            // Check if current key matches
            if (*keyPtr == *baseArray)
            {
                // Key found: return pointer to value
                return baseArray + 1;
            }

            // Stop if key is less than current key (maintain sorted order)
            if (*keyPtr < *baseArray) break;

            index++;
            baseArray += 2; // advance to next pair
        }
        while (index < count);
    }

    // Key not found -> allocate a new pair at the correct sorted position
    uint* newPair = (uint*)allocPair(); // FUN_00617a80
    newPair[0] = *keyPtr;
    newPair[1] = *valuePtr;
    return newPair + 1; // return pointer to the inserted value
}