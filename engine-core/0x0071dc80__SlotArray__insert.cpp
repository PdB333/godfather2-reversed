// FUNC_NAME: SlotArray::insert
int __thiscall SlotArray::insert(SlotArray *this, Slot *source) {
    // +0x60: count of active slots (max 8)
    unsigned int slotIndex = *(uint *)((char *)this + 0x60);
    // Array full, cannot add
    if (slotIndex > 7) {
        return 0;
    }
    // Pointer to the destination slot (each slot is 12 bytes)
    Slot *dest = (Slot *)((char *)this + slotIndex * sizeof(Slot));
    // Bump count
    *(uint *)((char *)this + 0x60) = slotIndex + 1;
    // Avoid self-assignment
    if (dest != source) {
        void *newObject = source->object;
        // Replace only if the object pointer changed
        if (dest->object != newObject) {
            // Release previous object if any
            if (dest->object != (void *)0x0) {
                FUN_004daf90(dest); // releaseSlot
            }
            dest->object = newObject;
            // If new object is non-null, link this slot into the object's slot list
            // The object has a pointer to its first slot at offset +4
            if (newObject != (void *)0x0) {
                dest->next = *(Slot **)((char *)newObject + 4);
                *(Slot **)((char *)newObject + 4) = dest;
            }
        }
    }
    // Copy the value field (third int)
    dest->value = source->value;
    return 1;
}