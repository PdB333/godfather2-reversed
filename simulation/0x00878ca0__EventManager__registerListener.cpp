// FUNC_NAME: EventManager::registerListener
// Address: 0x00878ca0
// This function registers a listener (param_2) for a given bit index (param_3).
// It maintains an array of 4 entries (each 12 bytes) at offset 0xed4.
// Each entry stores a key (pointer + 0x48) to a listener list head.
// If the key already exists, it adds the bit to the entry's flag field.
// Otherwise, it finds an empty slot and inserts a new entry, linking it into the list.

int __thiscall EventManager::registerListener(EventManager* this, void* listenerHead, int* bitIndexPtr)
{
    // Array of entries: each 12 bytes (int storedKey, int nextPtr, int flags)
    // at this + 0xed4
    struct NodeEntry {
        int storedKey; // +0x00
        int nextPtr;   // +0x04
        int flags;     // +0x08
    };
    NodeEntry* entries = (NodeEntry*)((char*)this + 0xed4);
    
    int emptySlotIndex = 4; // default invalid index
    int i;
    int key;
    int storedKey;
    int foundEntry = -1;
    
    // Search existing entries for a match
    for (i = 0; i < 4; i++) {
        storedKey = entries[i].storedKey;
        if (storedKey == 0) {
            key = 0;
        } else {
            key = storedKey - 0x48;
        }
        if (key == (int)listenerHead) {
            // Found matching entry
            foundEntry = i;
            if (i < 4) {
                goto setBit;
            }
            break;
        }
        // Track empty slot (storedKey == 0 or storedKey == 0x48)
        if (storedKey == 0 || storedKey == 0x48) {
            emptySlotIndex = i;
        }
    }
    
    // If no match found, try to allocate a new entry in an empty slot
    if (emptySlotIndex < 4) {
        NodeEntry* entry = &entries[emptySlotIndex];
        int newStoredKey;
        if (listenerHead == 0) {
            newStoredKey = 0;
        } else {
            newStoredKey = (int)listenerHead + 0x48;
        }
        if (entry->storedKey != newStoredKey) {
            // Destroy existing if any
            if (entry->storedKey != 0) {
                destroyEntry(entry); // FUN_004daf90 - cleanup old entry
            }
            entry->storedKey = newStoredKey;
            if (newStoredKey != 0) {
                // Link into the listener list: insert at head of list pointed by listenerHead
                // listenerHead has a 'next' field at offset 4
                int* nextField = (int*)((char*)listenerHead + 4);
                entry->nextPtr = *nextField;
                *nextField = (int)entry;
            }
        }
        // Fall through to set bit (emptySlotIndex used as foundEntry)
        foundEntry = emptySlotIndex;
    }
    
    if (foundEntry >= 0 && foundEntry < 4) {
        NodeEntry* entry = &entries[foundEntry];
        // Set the bit corresponding to the low byte of *bitIndexPtr
        entry->flags |= 1 << ((unsigned char)*bitIndexPtr & 0x1f);
        return 1;
    }
    return 0; // no empty slot available
}