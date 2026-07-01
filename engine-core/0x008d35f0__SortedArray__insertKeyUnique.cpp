// FUNC_NAME: SortedArray::insertKeyUnique
// Address: 0x008d35f0
// Role: Insert a unique key into a sorted array of 24-byte entries (key + 5 fields). Returns pointer to data part if inserted, NULL if duplicate.

uint* __thiscall SortedArray::insertKeyUnique(uint* this, uint* keyPtr) {
    int index = 0;
    if (this[1] > 0) { // element count
        uint* entry = (uint*)this[0]; // base pointer to array
        do {
            if (*keyPtr == *entry) {
                return nullptr; // key already exists
            }
            if (*keyPtr < *entry) {
                break; // insertion point found (key should come before current)
            }
            index++;
            entry += 6; // stride = 6*4 = 24 bytes
        } while (index < (int)this[1]);
    }

    // Insert a new element at 'index' position
    uint* newEntry = (uint*)FUN_008d34a0(index); // likely shifts elements and returns pointer to new slot
    *newEntry = *keyPtr; // store the key
    return newEntry + 1; // return pointer to the data part (first field after key)
}