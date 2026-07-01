// FUNC_NAME: ListManager::selectItem
void __thiscall ListManager::selectItem(int thisPtr, int param_2)
{
    int itemIndex;
    int *arrayEntry;
    int *currentItemPtr;
    int newItem;

    itemIndex = FUN_009210c0(param_2); // Convert param to index
    if (itemIndex < 0) {
        // Invalid index: clear current selection
        if (*(int *)(thisPtr + 0xa4) != 0) {
            FUN_004daf90((undefined4 *)(thisPtr + 0xa4)); // Free current selection node
            *(undefined4 *)(thisPtr + 0xa4) = 0;
        }
    } else {
        // Get pointer to array element (each 8 bytes: pointer + next?)
        arrayEntry = (int *)(*(int *)(thisPtr + 0x68) + itemIndex * 8);
        currentItemPtr = (int *)(thisPtr + 0xa4); // Pointer to current selection
        newItem = *arrayEntry; // Load the item pointer from the array

        // Update current selection if different
        if (*currentItemPtr != newItem) {
            if (*currentItemPtr != 0) {
                FUN_004daf90(currentItemPtr); // Free old selection node
            }
            *currentItemPtr = newItem; // Set new item
            if (newItem != 0) {
                // Store back-pointer: node->owner = thisPtr
                *(undefined4 *)(thisPtr + 0xa8) = *(undefined4 *)(newItem + 4);
                *(int **)(newItem + 4) = currentItemPtr; // Node's second field points to this object's member
            }
        }

        // Handle state transitions based on global game mode
        if (*(int *)(DAT_01130020 + 0x6c) != 2) {
            // Normal mode: set index and state
            *(int *)(thisPtr + 0x74) = itemIndex;
            *(int *)(thisPtr + 0x58) = 2; // State 2 (selected)
            return;
        }

        // Special mode (e.g., cutscene or dialogue)
        if (*(int *)(thisPtr + 0x58) != 2) {
            // Not already in selection state: set index and trigger action
            *(int *)(thisPtr + 0x74) = itemIndex;
            FUN_00956a50(2, 0); // Play selection animation
            return;
        }

        // Already in selection state: change index and update UI
        if (*(int *)(thisPtr + 0x74) != itemIndex) {
            *(int *)(thisPtr + 0x74) = itemIndex;
            FUN_00921680();          // Update highlight
            FUN_00402050(&DAT_011301c0, 0); // Show tooltip
            FUN_00921400();          // Refresh list
            return;
        }
    }
    return;
}