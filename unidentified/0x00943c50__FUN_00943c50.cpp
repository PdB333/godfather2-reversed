// FUNC_NAME: SomeManager::validateSlotProgress
// Address: 0x00943c50
// This function checks that for each slot (starting from index 1), the associated object's count is not greater than the current slot index.
// If any object's count exceeds the index, the function returns early (indicating not all slots are ready).
// Offsets: +0xf0 = pointer to slot array header (first 4 bytes: count? then array of SlotEntry), +0xf4 = total slot count

struct SomeObject {
    int field_0;          // +0x00
    uint m_count;         // +0x04
};

struct SlotEntry {
    SomeObject* pObject;  // +0x00
    int unused;           // +0x04
};

void SomeManager::validateSlotProgress() {
    uint slotCount = *(uint*)(this + 0xf4);
    if (slotCount == 0) {
        return;
    }

    // The slot array pointer points to a header; actual entries start at offset 4
    SlotEntry* entries = (SlotEntry*)(*(char**)(this + 0xf0) + 4);

    for (uint i = 1; i < slotCount; i++) {
        // If the object's count is greater than the current index, we are not ready
        if (i < entries[i].pObject->m_count) {
            return;
        }
    }
}