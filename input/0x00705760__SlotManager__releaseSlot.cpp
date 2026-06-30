// FUNC_NAME: SlotManager::releaseSlot
void __thiscall SlotManager::releaseSlot(unsigned int id) {
    if (id == 0) {
        return;
    }

    int index = getIndexFromId(id); // FUN_00704860 maps id to an array index
    Slot* slot = &m_slots[index];   // m_slots starts at this+20 (20 bytes header), each slot 20 bytes

    int* pPointer = &slot->pointer; // offset +4 within slot
    if (*pPointer != 0 && *pPointer != 0x48 && **reinterpret_cast<int**>(pPointer) != 0) {
        // Call deallocation function on the pointed-to object
        releaseObject(*pPointer); // FUN_004daf90
        *pPointer = 0;
    }

    // Clear the flag/refcount at slot->field_c (offset +0xc)
    slot->field_c = 0; // always set to 0 by the expression
}

// NOTE: The structure Slot is 20 bytes:
//   int unknown_0;      // +0x00
//   int* pointer;       // +0x04  (pointer to something, e.g. an object)
//   int unknown_8;      // +0x08
//   int field_c;        // +0x0c  (cleared after release)
//   int field_10;       // +0x10  (used to force field_c to 0)
// The array starts at offset 0x14 (20) from this.