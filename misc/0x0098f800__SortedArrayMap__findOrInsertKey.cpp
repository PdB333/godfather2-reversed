// FUNC_NAME: SortedArrayMap::findOrInsertKey
// Address: 0x0098f800
// Role: Searches a sorted array of key-value pairs (uint32 keys, uint32 values) for a given key.
// If found, returns nullptr. If not found, inserts a new entry at the correct sorted position
// and returns a pointer to the value field of the new entry (so caller can assign it).
// The array is stored as: [key0, value0, key1, value1, ...] with count in +0x04.
// Helper function FUN_0098f640 (insertSlotAt) handles memory allocation and shifting.

uint* __thiscall SortedArrayMap::findOrInsertKey(uint* thisPtr, uint* keyPtr)
{
    int index = 0;
    int count = (int)thisPtr[1]; // +0x04: number of elements
    if (0 < count) {
        uint* data = (uint*)thisPtr[0]; // +0x00: pointer to array
        do {
            if (*keyPtr == *data) {
                // Key already exists, return null
                return (uint*)0x0;
            }
            if (*keyPtr < *data) break; // insertion point found
            index++;
            data += 2; // move to next key-value pair
        } while (index < count);
    }
    // Insert new slot at 'index' (shift elements right)
    uint* newSlot = (uint*)insertSlotAt(index); // FUN_0098f640
    *newSlot = *keyPtr; // store key
    return newSlot + 1; // return pointer to value part
}