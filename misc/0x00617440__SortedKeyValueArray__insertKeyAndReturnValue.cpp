// FUNC_NAME: SortedKeyValueArray::insertKeyAndReturnValue

struct SortedKeyValueArray {
    uint32* data;   // +0x00 - pointer to array of key-value pairs (each 2 uint32s)
    int32_t count;  // +0x04 - number of pairs currently stored
};

// External helper: makes room for insertion at given index and returns pointer to the key slot
uint32* insertSpaceAt(SortedKeyValueArray* arr, int32_t index);

// Insert a key into the sorted array; returns pointer to the value part (key+1) on success, or nullptr if duplicate.
uint32* SortedKeyValueArray::insertKeyAndReturnValue(uint32* keyPtr)
{
    int32_t i = 0;

    if (this->count > 0) {
        uint32* currentPair = this->data;
        do {
            if (*keyPtr == *currentPair) {
                return nullptr; // duplicate key, insertion fails
            }
            if (*keyPtr < *currentPair) {
                break; // insertion point found
            }
            i++;
            currentPair += 2; // move to next key-value pair
        } while (i < this->count);
    }

    // Insert at index i
    uint32* newKeySlot = insertSpaceAt(this, i);
    *newKeySlot = *keyPtr;
    return newKeySlot + 1; // address of the value slot
}