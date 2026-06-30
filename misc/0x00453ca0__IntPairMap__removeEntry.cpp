// FUNC_NAME: IntPairMap::removeEntry
// Address: 0x00453ca0
// Role: Removes an entry by key from a compact array of key-value pairs, only if the value is non-zero.
// The data structure: at this+0x4c is a pointer to an array of int pairs [key, value], and at this+0x50 is the count of entries.
// After removal, the last entry is moved into the vacated slot to keep the array contiguous.

void IntPairMap::removeEntry(int key)
{
    uint count = this->count;            // +0x50: number of entries
    if (count == 0)
        return;

    int* entries = this->data;           // +0x4c: pointer to array of (key, value) pairs
    int* current = entries;
    uint index = 0;

    // Search for the key
    while (*current != key)
    {
        index++;
        current += 2;
        if (index >= count)
            return;                     // key not found
    }

    // Only remove if the value is non-zero (observed behavior)
    if (current[1] != 0)
    {
        uint lastIndex = count - 1;
        if (index != lastIndex)
        {
            // Move the last entry to the removed slot
            entries[index * 2]     = entries[lastIndex * 2];
            entries[index * 2 + 1] = entries[lastIndex * 2 + 1];
        }
        this->count = count - 1;        // decrement count
    }
}