// FUNC_NAME: EARS::Map::insertOrGet
uint* __thiscall Map::insertOrGet(uint* thisPtr, uint* keyPtr, uint* valuePtr)
{
    uint key = *keyPtr;
    uint value = *valuePtr;
    int size = *(int*)(thisPtr + 4);       // +0x04: number of elements
    uint* dataArray = (uint*)*thisPtr;     // +0x00: pointer to array of pairs (key,value)

    int index = 0;
    if (size > 0) {
        do {
            uint currentKey = dataArray[index * 2];
            if (currentKey == key) {
                return &dataArray[index * 2 + 1]; // return pointer to stored value
            }
            if (key < currentKey) break; // keys are sorted, stop searching
            index++;
        } while (index < size);
    }

    // Not found: allocate a new pair and insert it at position 'index'
    uint* newPair = allocatePair(); // FUN_00617a80 - returns pointer to allocated pair (2 uints)
    newPair[0] = key;
    newPair[1] = value;
    return &newPair[1];
}