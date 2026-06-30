// FUNC_NAME: SortedArrayMap::tryInsertOrGetValueSlot
// Function at 0x006b4d50: Inserts a key into a sorted array map if not present, returns pointer to value slot or null if exists.
// Container layout: +0x00: pointer to array of (uint32 key, uint32 value) pairs, +0x04: count of pairs
// The array is maintained sorted by key ascending.

uint32* __thiscall SortedArrayMap::tryInsertOrGetValueSlot(
    uint32* container,   // this: points to container header
    uint32* keyPtr       // points to the key to insert
)
{
    int32_t i;               // insertion index
    uint32* pairs;           // array of key-value pairs
    int32_t count;

    i = 0;
    count = (int32_t)container[1];           // +0x04: number of pairs currently stored

    if (0 < count) {
        pairs = (uint32*)*container;        // +0x00: base pointer to pair array
        do {
            // Compare keys: if found equal, return null (already present)
            if (*keyPtr == *pairs) {
                return (uint32*)0x0;
            }
            // If new key is smaller than current key, we break to insert at this position
            if (*keyPtr < *pairs) break;

            i++;
            pairs += 2;                     // each pair is 8 bytes (two uint32)
        } while (i < count);
    }

    // Key not found; insert new node at index i
    uint32* newNode = (uint32*)FUN_006b4540(i);  // allocate and shift pairs, return pointer to new node's key slot
    *newNode = *keyPtr;                            // store the key
    return newNode + 1;                            // return pointer to the value slot (to be filled by caller)
}