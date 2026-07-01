// FUNC_NAME: KeyValueArray::insertKey
// Function address: 0x009442b0
// Role: Inserts a key into a sorted array of key-value pairs (each 8 bytes: key, value).
//       If key already exists, returns nullptr.
//       Otherwise, makes room at the correct sorted position and returns pointer to the value slot.
// Structure layout assumed:
//   +0x00: uint* m_pairs (pointer to array of uint[2] per element)
//   +0x04: int   m_count (number of valid elements)
// Note: The array must be sorted by key (ascending). The helper FUN_00943150 likely shifts elements or allocates space.

uint* __thiscall KeyValueArray::insertKey(KeyValueArray* thisPtr, uint* keyPtr) {
    int index = 0;
    int count = thisPtr->m_count;                  // param_1[1]

    if (count > 0) {
        uint* pairs = thisPtr->m_pairs;            // *param_1
        do {
            uint currentKey = pairs[0];            // *puVar2 (key part of current pair)
            uint newKey = *keyPtr;                 // *param_2

            // If key matches, insertion fails
            if (newKey == currentKey) {
                return nullptr;                    // 0x0
            }
            // If new key is smaller, break to insert before current
            if (newKey < currentKey) {
                break;
            }

            index++;
            pairs += 2;                            // sizeof(uint) * 2 = 8 bytes per pair
        } while (index < count);
    }

    // Helper function to make room at index (likely shifts elements and returns pointer to new slot)
    uint* slot = FUN_00943150(index);              // allocate space for new pair at position index
    *slot = *keyPtr;                               // store the key in first part of the pair
    return slot + 1;                               // return pointer to the value part of the new pair
}