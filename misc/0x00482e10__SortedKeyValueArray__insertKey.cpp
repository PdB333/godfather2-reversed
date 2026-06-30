// FUNC_NAME: SortedKeyValueArray::insertKey
uint* SortedKeyValueArray::insertKey(uint* keyPtr)
{
    int i = 0;
    // 'this' pointer has:
    // +0x00: uint* data    - pointer to array of key-value pairs (each 2 uints)
    // +0x04: int   count   - number of pairs in array
    if (this->count > 0)
    {
        uint* currentPair = this->data;
        do
        {
            // Compare keys (keys are first element of each pair)
            if (*keyPtr == *currentPair)
            {
                return nullptr; // Duplicate key, insertion not allowed
            }
            if (*keyPtr < *currentPair)
            {
                break; // Found insertion point before current pair
            }
            i++;
            currentPair += 2; // Move to next key-value pair
        } while (i < this->count);
    }

    // Allocate a new pair slot.
    // The function FUN_00482fd0 likely shifts elements to make room
    // and returns a pointer to the empty slot for the new key.
    uint* newPair = AllocateNewPair(); // Placeholder for FUN_00482fd0
    *newPair = *keyPtr;               // Store the key
    return newPair + 1;               // Return pointer to the value slot
}