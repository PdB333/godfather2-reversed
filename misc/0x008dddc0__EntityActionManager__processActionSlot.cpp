// FUNC_NAME: EntityActionManager::processActionSlot
void __thiscall EntityActionManager::processActionSlot(EntityActionManager* this, Entity* entity) {
    // entity is the object whose action slot is being processed
    if (entity != nullptr) {
        // Check if the entity's slot index is within range (max 24 slots)
        if ( *(byte*)(entity + 0x1AC) < 0x19 ) {
            // Calculate pointer to the action slot data in this manager's array
            // The array is at offset 0x24 from this, each slot is 12 bytes (0xC)
            int slotIndex = *(byte*)(entity + 0x1AC);  // +0x1AC: current action slot index
            int* slotData = (int*)(*(int*)(this + 0x24) + 4 + slotIndex * 0xC);

            // Dereference the first 4 bytes of the slot to check its state
            int slotState = *slotData;
            if (slotState != 0 && slotState != 0x48) {  // 0x48 = SLOT_STATE_INVALID
                if (*slotData != 0) {
                    executeSlotAction();  // FUN_008dd250
                    return;
                }
                executeSlotAction();  // FUN_008dd250
                return;
            }
        }
    }
    return;
}