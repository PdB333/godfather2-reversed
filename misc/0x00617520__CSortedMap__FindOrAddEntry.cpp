// FUNC_NAME: CSortedMap::FindOrAddEntry
// Address: 0x00617520
// This function searches a sorted array of key-value pairs (uint32 each) stored in a map structure.
// If the key is found, returns a pointer to its associated value.
// If not found, allocates a new pair (key-value) via an external allocation function and returns
// a pointer to the new value. The array is assumed to be sorted by key for the search,
// but insertion does not maintain the sort order (new pairs are appended).

struct CSortedMap {
    uint32* data;   // +0x00 pointer to array of pairs (key, value)
    int32 count;    // +0x04 number of pairs in the array
};

// External allocation function (returns pointer to a new key-value pair)
extern "C" uint32* AllocatePair(void); // FUN_006179b0

uint32* __thiscall CSortedMap::FindOrAddEntry(const uint32* key, const uint32* value)
{
    int32 i;
    uint32* currentPair;

    i = 0;
    if (0 < this->count) {
        currentPair = this->data;
        do {
            if (*key == *currentPair) {
                // Found: return pointer to the value (second uint of the pair)
                return this->data + i * 2 + 1;
            }
            if (*key < *currentPair) break; // Assume sorted order, stop early if key is smaller
            i++;
            currentPair += 2;
        } while (i < this->count);
    }

    // Key not found: allocate new pair and store key/value
    currentPair = AllocatePair();
    *currentPair = *key;
    currentPair[1] = *value;
    // Return pointer to the value part of the new pair
    return currentPair + 1;
}