// FUNC_NAME: KeyValueStore::findOrCreateValue
// Function at 0x00617520: Looks up a key in a sorted array of uint pairs (key at +0x00, value at +0x04 within each pair).
// If found, returns pointer to the value. Otherwise, allocates a new pair and returns pointer to its value.
// Note: The new pair is not inserted into the array – this may indicate external management of the array.

uint* KeyValueStore::findOrCreateValue(uint* pKey, uint* pValue) {
    int i = 0;
    if (0 < this->count) {                       // this->count at +0x04
        uint* pPair = this->array;                // this->array at +0x00
        do {
            if (*pKey == *pPair) {
                return pPair + 1;                 // pointer to the value part of the pair
            }
            if (*pKey < *pPair) break;            // break if key would belong before current pair
            i++;
            pPair += 2;                           // advance to next pair (2 uint32s)
        } while (i < this->count);
    }
    uint* newPair = allocPair();                  // FUN_006179b0 – memory allocator for a new pair
    *newPair = *pKey;
    newPair[1] = *pValue;
    return newPair + 1;                           // pointer to the value part of the new pair
}