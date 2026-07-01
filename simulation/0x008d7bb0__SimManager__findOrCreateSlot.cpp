// FUNC_NAME: SimManager::findOrCreateSlot
int __thiscall SimManager::findOrCreateSlot(int this, undefined4 key)
{
    int index;
    int *slotPtr;

    // Look up the key in a hash table; returns an index or -1 if not found.
    index = FUN_008d72e0(&key);
    // If index is valid and the slot table exists, compute the slot address.
    // The slot table is at *(this+0x38) + 4, each slot is 0x18 bytes.
    // Check both conditions: if index invalid OR base pointer is null -> fallback.
    if ((index < 0) ||
        (slotPtr = *(int **)(this + 0x38) + 4 + index * 0x18, slotPtr == nullptr))
    {
        // Fallback: create or retrieve a new slot via another lookup.
        slotPtr = FUN_008d77e0(&key);
        // Post-creation initialization (e.g., notify listeners).
        FUN_008d5e80();
    }
    // Return pointer to the slot (as int for compatibility).
    return (int)slotPtr;
}