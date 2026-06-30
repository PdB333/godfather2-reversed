// FUNC_NAME: ObjectSlotManager::addSlot
uint __thiscall ObjectSlotManager::addSlot(uint32_t *this, int *object, uint desiredSlot)
{
    uint slot;
    uint numSlots;
    int *slotArray;

    if (desiredSlot == 0xFFFFFFFF) {
        // Find an empty slot
        slot = 0;
        numSlots = *(uint *)(this + 8);  // +0x08: maximum number of slots
        if (numSlots != 0) {
            slotArray = *(int **)(this + 4);  // +0x04: pointer to array of slot pointers
            do {
                if (*slotArray == 0) {
                    // Empty slot found, store the object pointer
                    *(int **)(*(int *)(this + 4) + slot * 4) = object;
                    // Initialize the object and register it with the class system
                    // First virtual call: object->getClassRep() (offset +0x0C in vtable)
                    int classRep = (**(int (**)(void))(*(int *)object + 0xC))();
                    // Second virtual call: classRep->registerInstance() (offset +0x50 in vtable from field at +0x54)
                    (**(void (**)(void))(*(int *)(classRep + 0x54) + 0x50))();
                    // Increment generation counter
                    *(uint *)(this + 0xC) += 1;  // +0x0C: insertion generation counter
                    return slot;
                }
                slot++;
                slotArray++;
            } while (slot < numSlots);
            // No empty slot found
            *(uint *)(this + 0xC) += 1;
            return 0xFFFFFFFF;
        }
    } else {
        // Insert at the given slot (replacing any previous pointer)
        *(int **)(*(int *)(this + 4) + desiredSlot * 4) = object;
    }
    // Fallback: when desiredSlot == -1 but no slots (numSlots == 0), or after specific slot insert
    *(uint *)(this + 0xC) += 1;
    return desiredSlot;
}