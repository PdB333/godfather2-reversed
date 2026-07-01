// FUNC_NAME: UIListManager::refreshSelection
void __thiscall UIListManager::refreshSelection(int thisPtr) {
    // +0x58: pointer to list container (e.g., UIListContainer*)
    int *containerBase = *(int **)(thisPtr + 0x58);
    // +0xff0: pointer to current list node (e.g., ListNode*)
    int *currentNodePtr = *(int **)(containerBase + 0xff0);
    int ownerPtr;

    if (currentNodePtr != (int *)0x0) {
        // Subtract offset that points from node back to its owner structure
        // Typically node is a member of the owner at offset 0x48
        ownerPtr = (int)((char *)currentNodePtr - 0x48);
    } else {
        ownerPtr = 0;
    }

    // Retrieve data from the container for the given owner
    int result = FUN_007b1060((int)containerBase, ownerPtr);
    // +0x1b0: store the result as a member (e.g., currentSelection)
    *(int *)(thisPtr + 0x1b0) = result;
}