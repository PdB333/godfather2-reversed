//FUNC_NAME: SortedMap::insertKey
uint* SortedMap::insertKey(uint* keyPtr) {
    int i = 0;
    if (0 < this->count) {
        uint* currentPair = this->pairs;
        do {
            if (*keyPtr == *currentPair) {
                return nullptr; // duplicate key
            }
            if (*keyPtr < *currentPair) break;
            i++;
            currentPair += 2; // advance to next key-value pair
        } while (i < this->count);
    }
    // Allocate new pair slot at insertion point
    uint* newPair = (uint*)FUN_005be0d0();
    *newPair = *keyPtr; // store key
    return newPair + 1; // return pointer to value slot
}