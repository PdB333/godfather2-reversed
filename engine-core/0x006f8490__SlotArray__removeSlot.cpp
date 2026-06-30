// FUNC_NAME: SlotArray::removeSlot
// Address: 0x006f8490
// This function removes a slot from a fixed-size array of 12-byte structures.
// Slots hold a pointer to an object (offset0), a linked list pointer (offset4),
// and a byte flag (offset8). After removal, subsequent slots are shifted left,
// and the linked list pointers are updated to maintain consistency.
// The last slot becomes empty and is cleaned up.

void __thiscall SlotArray::removeSlot(int this, uint slotIndex) {
    // this: pointer to struct { Slot* slots; uint count; }
    // slots: pointer to array of Slot (each 12 bytes)
    // count: number of valid slots

    uint count = *(int *)(this + 4); // param_1[1]
    Slot* slots = *(Slot**)this;     // param_1[0]

    if (slotIndex < count - 1) {
        // Shift all slots after slotIndex left by one
        for (uint i = slotIndex; i < count - 1; i++) {
            Slot* current = &slots[i];
            Slot* next = &slots[i + 1];

            // Check if the object pointer differs between current and next
            if (current->object != next->object) {
                // If current has an existing object, destroy it (or release)
                if (current->object != 0) {
                    FUN_004daf90(current); // Assume cleanup function
                }
                // Copy object pointer from next slot
                current->object = next->object;
                if (next->object != 0) {
                    // Update linked list: current->prev = next->object->next
                    current->prev = *(int*)(next->object + 4);
                    // Set next->object->next to point back to current
                    *(int**)(next->object + 4) = current;
                }
            }
            // Copy the byte flag from next slot (low byte of third int)
            *(char*)(&current->flag) = (char)(next->flag);
        }
    }

    // Decrement the count (effectively removing the last slot)
    count--;
    *(int*)(this + 4) = count;

    // Clean up the now-empty last slot if it still has an object
    Slot* lastSlot = &slots[count]; // index after decrement is the old last
    if (lastSlot->object != 0) {
        FUN_004daf90(lastSlot); // Release the object
    }
}