// FUNC_NAME: InventoryManager::setCurrentItem
void __fastcall InventoryManager::setCurrentItem(int this) {
    uint index;
    undefined4 dataPtr;
    int* itemArray;
    int newItem;
    undefined4 copySize;

    // Search for item matching current selection criteria
    index = 0;
    if (*(int*)(this + 0x24) != 0) {
        itemArray = *(int**)(this + 0x20); // array of item pointers at +0x20
        do {
            newItem = *itemArray;
            // Compare item type (at +0x74) with target type from current item's associated data (at +0x1c -> +0xc0)
            if (*(int*)(newItem + 0x74) == *(int*)(*(int*)(this + 0x1c) + 0xc0)) {
                goto found;
            }
            index++;
            itemArray++;
        } while (index < *(uint*)(this + 0x24));
    }
    newItem = 0;
found:
    // Release old current item if it exists
    if (*(int*)(this + 0x1c) != 0) {
        releaseItem(); // FUN_008fbcf0 - likely clean up previous item
    }

    // Set new current item
    *(int*)(this + 0x1c) = newItem;

    // Allocate and copy data for the new item (size 0x248 = 584 bytes)
    copySize = 0x248;
    dataPtr = allocateData(newItem + 0xec); // FUN_008fc140 - get pointer to storage at offset 0xec
    copyItemData(dataPtr, copySize); // FUN_008fd000 - initialize from that storage
    finalizeOperation(0); // FUN_008fcb40 - commit changes
    return;
}