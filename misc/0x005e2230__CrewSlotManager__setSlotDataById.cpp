// FUNC_NAME: CrewSlotManager::setSlotDataById
// Address: 0x005e2230
// Searches a fixed-size array of 5 slots for a matching entity ID and stores data.
// Slot structure: +0x000 -> data field, +0x244 -> key (entity ID). Array of 5 slots starts at this+0x24C.
// The key array at this+0x490 directly accesses the key field of each slot.

bool CrewSlotManager::setSlotDataById(int entityId, void* data) {
    // entityId passed in ESI (unaff_ESI)
    // 'this' in EDI (unaff_EDI)

    if (entityId == 0) {
        return false;
    }

    // Pointer to the first key in the slot array (this + 0x490)
    int* keyPtr = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x490);

    for (int i = 0; i < 5; ++i) {
        // Compare current slot's key with the requested entity ID
        if (*keyPtr == entityId) {
            // Found slot, compute its base address: this + 0x24C + i * 0x4a4
            int* slotBase = reinterpret_cast<int*>(
                reinterpret_cast<char*>(this) + 0x24C + i * 0x4a4);
            // Store the data in the first field of the slot (offset +0x000 from slot base)
            *slotBase = reinterpret_cast<int>(data);
            return true;
        }
        // Advance to the next key (each slot is 0x4a4 bytes, so key is spaced by 0x4a4)
        keyPtr = reinterpret_cast<int*>(
            reinterpret_cast<char*>(keyPtr) + 0x4a4);
    }

    return false;
}