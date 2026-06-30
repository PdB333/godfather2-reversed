// FUNC_NAME: EventManager::processSlot
void EventManager::processSlot(uint size) {
    // size must be at least 0x1000 (4KB), else call error handler
    if (size < 0x1000) {
        FUN_0059bf00(); // likely error/assert
        return;
    }

    // currentSlot is stored in member variable (likely m_currentSlot, but here from register EDI)
    if (currentSlot < 0 || currentSlot >= slotCount) {
        FUN_0059bf00();
        return;
    }

    SlotEntry* slot = &slotArray[currentSlot]; // each slot is 8 bytes: count at +0, items pointer at +4
    int itemCount = slot->count;
    if (itemCount <= 0) {
        return;
    }

    int** itemArray = (int**)slot->items; // pointer to array of pointers to items
    for (int i = 0; i < itemCount; i++) {
        int* item = itemArray[i];
        // item layout: +0 type, +4 data
        if (item[0] == 1) {
            // Type 1: call sub function with data, size, and -1
            FUN_005af370(item[1], size, 0xFFFFFFFF);
        }
    }
}