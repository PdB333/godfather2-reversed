// FUNC_NAME: ObjectManager::removeById
void __thiscall ObjectManager::removeById(int id)
{
    uint activeIndex = 0;
    uint activeCount = *(uint *)(this + 0xac); // +0xac: number of entries in active list

    // Check if ID exists in the active list (at +0xa8)
    if (activeCount != 0) {
        int *activeList = *(int **)(this + 0xa8); // +0xa8: pointer to array of active IDs
        do {
            if (activeList[activeIndex] == id) {
                // ID found in active list -> call specialized removal handler
                if ((int)activeIndex >= 0) {
                    removeActiveById(activeIndex);  // FUN_006b56a0
                }
                break;
            }
            activeIndex++;
            activeList++;
        } while (activeIndex < activeCount);
    }

    // Now check the pending list (at +0xb4, count at +0xb8)
    uint pendingCount = *(uint *)(this + 0xb8); // +0xb8: number of entries in pending list
    uint pendingIndex = 0;
    if (pendingCount != 0) {
        int *pendingList = *(int **)(this + 0xb4); // +0xb4: pointer to array of pending IDs
        while (pendingList[pendingIndex] != id) {
            pendingIndex++;
            pendingList++;
            if (pendingCount <= pendingIndex) {
                return; // ID not found in either list
            }
        }
        // ID found in pending list -> remove it by swapping with last element
        if ((int)pendingIndex >= 0) {
            if (pendingIndex != pendingCount - 1) {
                // Overwrite the found element with the last element
                *(int *)(*(int *)(this + 0xb4) + pendingIndex * 4) =
                    *(int *)(*(int *)(this + 0xb4) + (pendingCount - 1) * 4);
            }
            // Decrement count and notify
            *(int *)(this + 0xb8) = pendingCount - 1;
            onListChanged();  // FUN_00791350
        }
    }
}