// FUNC_NAME: SomeManager::processPendingAction
void __thiscall SomeManager::processPendingAction(SomeManager* this) {
    // Get next pending index from internal queue (FUN_00941490)
    int index = getNextPendingIndex();
    if (index >= 0) {
        // Access array at this+0xf0 (array of 8-byte entries)
        // Each entry: first 4 bytes unknown, second 4 bytes are the item to process
        int* arrayBase = *(int**)((char*)this + 0xf0);
        int item = *(int*)((char*)arrayBase + 4 + index * 8);
        // Process the pending item (FUN_00943f50)
        processPendingItem(item);
        // Clear the pending slot (FUN_00941a40)
        clearPendingItem(index);
    }
}