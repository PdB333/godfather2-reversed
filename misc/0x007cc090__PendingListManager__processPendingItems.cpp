// FUNC_NAME: PendingListManager::processPendingItems

void __thiscall PendingListManager::processPendingItems(bool param_2)
{
    // Offset fields:
    // this+0x58: Pointer to first pending list (list A)
    // this+0x1b4: Pointer to second pending list (list B)
    // this+0x1c0: Pointer to iterator object (has vtable)

    int listAHead = *(int *)(this + 0x58);
    int tempListA = 0;  // Local list head for list A
    int tempListAHeadSaved = 0;  // Saved original next pointer
    int tempListB = 0;  // Local list head for list B
    int tempListBHeadSaved = 0;

    // Move all elements from list A to local temporary list A
    if (listAHead != 0 && *(int *)(listAHead + 0x48) != 0) { // Check if list has at least one element
        tempListAHeadSaved = *(int *)(listAHead + 0x4c); // Save original next pointer
        *(int **)(listAHead + 0x4c) = &tempListA;       // Redirect to local list
        tempListA = listAHead + 0x48;                   // Set local head to first element
    }

    // Move all elements from list B to local temporary list B
    if (&tempListB != (int *)(this + 0x1b4)) { // Avoid self-assignment
        int listBHead = *(int *)(this + 0x1b4);
        if (listBHead != 0) {
            tempListBHeadSaved = 0;
            tempListB = listBHead;                    // Move head to local list
            *(int *)(listBHead + 4) = (int)&tempListB; // Redirect to local list
        }
    }

    // If param_2 is true, reinitialize the iterator with list A
    if (param_2) {
        int newIterator = (**(code (__thiscall **)(int))(*(int *)(this + 0x1c0) + 8))(&tempListA);
        *(int *)(this + 0x1c0) = newIterator;
    }

    // Iterate through list A using the iterator
    int currentIterator = *(int *)(this + 0x1c0);
    while (currentIterator != 0) {
        bool hasMore = (**(code (__thiscall **)(int))(*(int *)(this + 0x1c0) + 0x10))();
        if (!hasMore) break;
        currentIterator = (**(code (__thiscall **)(int))(*(int *)(this + 0x1c0) + 8))(&tempListA);
        *(int *)(this + 0x1c0) = currentIterator;
    }

    // Free the temporary lists
    if (tempListB != 0) {
        FUN_004daf90(&tempListB); // likely deletes list nodes
    }
    if (tempListA != 0) {
        FUN_004daf90(&tempListA);
    }
}