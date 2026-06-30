// FUNC_NAME: OrderedUintMap::findOrCreateValue
uint * __thiscall OrderedUintMap::findOrCreateValue(uint *keyPtr)
{
    int index;
    uint *currentPair;

    index = 0;
    if (0 < this->count)
    {
        currentPair = this->data;
        do
        {
            if (*keyPtr == *currentPair)
            {
                // Key already exists, return null (no insertion)
                return (uint *)0x0;
            }
            if (*keyPtr < *currentPair) break;
            index = index + 1;
            currentPair = currentPair + 2; // skip key and value
        } while (index < this->count);
    }
    // Insert new key at position 'index'
    currentPair = insertPairAtIndex(index);
    *currentPair = *keyPtr; // store the key
    return currentPair + 1; // return pointer to the value slot
}