// FUNC_NAME: GhostManager::clearStaleEntries
void GhostManager::clearStaleEntries(void) {
    GhostManager* manager = this; // in_EAX
    while (manager != nullptr) {
        int count = manager->slotCount; // +0x1c: number of items in fixed-size array
        while (count != 0) {
            count--;
            int type = manager->fixedArray[count].type; // +0xc base, elements 8 bytes: [0]=type, [1]=objectPtr
            GhostObject* obj = manager->fixedArray[count].objectPtr;
            if (type == 4) {
                *(obj->flags + 5) |= 1; // set bit 0 at offset 5 (e.g., needsUpdate)
                type = manager->fixedArray[count].type;
            }
            if ((type > 3) && ((*(obj->flags + 5) & 1) == 0)) {
                manager->fixedArray[count].type = 0; // mark as unused
            }
        }

        int numSlots = 1 << (manager->dynamicSlotBitmask & 0x1f); // +0x7: bitmask yields count of dynamic slots
        if (numSlots != 0) {
            int slotIndex = numSlots * 0x14; // each dynamic slot is 20 bytes
            do {
                slotIndex -= 0x14;
                GhostSlot* slot = &manager->dynamicArray[slotIndex / 0x14]; // +0x10 base
                numSlots--;
                int slotType = slot->type; // offset 8 in slot structure
                GhostObject* obj2 = slot->objectPtr; // offset 12
                if (slotType == 4) {
                    *(obj2->flags + 5) |= 1;
                    slotType = slot->type;
                }
                if ((slotType > 3) && ((*(obj2->flags + 5) & 1) == 0)) {
                    slot->type = 0;
                }
                if ((slot->id > 3) && (slot->type == 0)) { // after possible reset, check id
                    slot->id = -1;
                }
            } while (numSlots != 0);
        }

        manager = manager->nextManager; // +0x18: linked list of managers
    }
}