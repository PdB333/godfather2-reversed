// FUNC_NAME: ItemManager::removeItem

void __thiscall ItemManager::removeItem(int this, int itemIdentifier)
{
    uint index;
    uint count;
    int *itemArray;

    // Search in first list (e.g., active items) at offset +0xa8 (array) and +0xac (count)
    if (*(uint *)(this + 0xac) != 0) {
        itemArray = *(int **)(this + 0xa8);
        for (index = 0; index < *(uint *)(this + 0xac); index++) {
            if (itemArray[index] == itemIdentifier) {
                if ((int)index >= 0) {
                    removeAtIndex(index);  // FUN_006b56a0 - remove from first list
                }
                break;
            }
        }
    }

    // Search in second list (e.g., pending items) at offset +0xb4 (array) and +0xb8 (count)
    count = *(uint *)(this + 0xb8);
    if (count != 0) {
        itemArray = *(int **)(this + 0xb4);
        for (index = 0; index < count; index++) {
            if (itemArray[index] == itemIdentifier) {
                if ((int)index >= 0) {
                    // If not the last element, move last element to this slot
                    if (index != count - 1) {
                        *(int *)(*(int *)(this + 0xb4) + index * 4) = *(int *)(*(int *)(this + 0xb4) + (count - 1) * 4);
                    }
                    // Decrement count
                    *(int *)(this + 0xb8) = count - 1;
                    // Rehash or update internal state after removal
                    rehash(this);  // FUN_00791350
                }
                return;
            }
        }
    }
}