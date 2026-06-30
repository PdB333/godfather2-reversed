// FUNC_NAME: ObjectWithSlots::findSlotForID
// Function at 0x006f3b80: Searches for a slot matching a given ID, returning pointer to the slot's base address.
// Slots are 0x34 bytes each, starting at offsets 0x10, 0x44, 0x78, 0xac (slot 0,1,2,3).
// Checked in reverse order (slot3→slot0) via a helper that validates the ID.

int __thiscall findSlotForID(void* this_, int id) {
    // Try slot at +0xac (slot 3)
    int slotBase = reinterpret_cast<int>(this_) + 0xac;
    if (checkIDMatch(id)) {
        return slotBase;
    }

    // Try slot at +0x78 (slot 2)
    slotBase = reinterpret_cast<int>(this_) + 0x78;
    if (checkIDMatch(id)) {
        return slotBase;
    }

    // Try slot at +0x44 (slot 1)
    slotBase = reinterpret_cast<int>(this_) + 0x44;
    if (checkIDMatch(id)) {
        return slotBase;
    }

    // Try slot at +0x10 (slot 0)
    slotBase = reinterpret_cast<int>(this_) + 0x10;
    if (checkIDMatch(id)) {
        return slotBase;
    }

    // No matching slot found
    return 0;
}