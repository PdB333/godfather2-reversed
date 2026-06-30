// FUNC_NAME: EntryManager::findOrAllocateEntry
// Function at 0x005247a0: Searches for an entry with a given key. If found, returns pointer to it.
// If not found and space available (max 5 entries), allocates a new entry, inserts it into a linked list, and returns it.
// Class layout:
// +0x50: some object (likely linked list head manager) passed to FUN_00522bf0
// +0x90: array of 5 entries, each 0xA0 bytes (160 bytes)
// +0x450: count of active entries (char, max 5)
// Entry layout:
// +0x00: stored value: if key==0 -> 0; if key!=0 -> reinterpret_cast<int*>((key + 4) as a pseudo-pointer)
// +0x04: next pointer in linked list (singly linked)
int* __thiscall EntryManager::findOrAllocateEntry(int key) {
    char count = *(char*)(this + 0x450);
    int i = 0;
    // Search existing entries
    if (count > 0) {
        int* entryPtr = (int*)(this + 0x90);
        do {
            int storedVal = *entryPtr;
            int actualKey;
            if (storedVal == 0) {
                actualKey = 0;
            } else {
                actualKey = storedVal - 4; // Stored value is key+4 for non-zero keys
            }
            if (actualKey == key) {
                // Found: return pointer to the entry's start in the array
                return (int*)(i * 0xA0 + 0x90 + this);
            }
            i++;
            entryPtr += 0x28; // Advance by 0x28 ints = 0xA0 bytes per entry
        } while (i < count);
    }

    // Not found, check if we have room (max 5)
    if (count > 5) {
        return nullptr;
    }

    // Allocate new entry at position 'count'
    int* newEntry = (int*)(count * 0xA0 + 0x90 + this);
    // Update count
    *(char*)(this + 0x450) = count + 1;

    // Transform key to stored value
    int storedKey;
    if (key == 0) {
        storedKey = 0;
    } else {
        storedKey = key + 4; // Encode as pseudo-pointer? (key+4 used for list linking)
    }

    int oldStoredVal = *newEntry;
    if (oldStoredVal != storedKey) {
        // If the entry was previously used (non-zero), unlink it from the linked list
        if (oldStoredVal != 0) {
            // Find predecessor in the linked list (assumes list starts at some head)
            int* prevNext = *(int**)(oldStoredVal + 4); // Get the next pointer of the node pointed to by oldStoredVal
            while (prevNext != newEntry) {
                prevNext = *(int**)((int)prevNext + 4);
            }
            // Unlink newEntry from the list
            *(int**)((int)prevNext + 4) = *(int**)((int)newEntry + 4);
        }
        // Set new stored value
        *newEntry = storedKey;
        if (storedKey != 0) {
            // Insert newEntry at the front of the linked list
            *(int**)((int)newEntry + 4) = *(int**)(storedKey + 4); // new entry's next = old head's next
            *(int**)(storedKey + 4) = newEntry; // The node pointed to by storedKey now points to newEntry
        }
    }

    // Call some update function on the object at offset 0x50 (likely list head management)
    FUN_00522bf0(this + 0x50);

    return newEntry;
}