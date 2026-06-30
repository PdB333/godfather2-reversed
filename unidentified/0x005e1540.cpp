// FUN_005e1540: TreeIterator::findNextActiveNode
// This function advances the iterator to the next active node (flag at +0x15 != 0) in a tree structure.
// The tree node layout:
//   +0x00: parent pointer
//   +0x04: next sibling pointer
//   +0x08: first child pointer
//   +0x15: active flag (char, 0 = inactive, non-zero = active)
// The iterator stores:
//   +0x00: root sentinel (must be non-null)
//   +0x04: current node pointer (updated during traversal)
// If no valid next node is found, an assertion is triggered.

void __thiscall TreeIterator::findNextActiveNode(void)
{
    // Assert that the root sentinel exists.
    if (*(int *)this == 0) {
        FUN_00b97aea(); // assertion/error
    }

    int *currentNode = *(int **)(this + 4); // +0x04: current node pointer
    char activeFlag = *(char *)((int)currentNode + 0x15); // node+0x15: active flag

    if (activeFlag == '\0') {
        // Current node is inactive: try to find an active ancestor or sibling.
        int *parentNode = (int *)*currentNode; // node+0x00: parent
        char parentActive = *(char *)((int)parentNode + 0x15);

        if (parentActive == '\0') {
            // Parent is also inactive: descend through the parent's child chain.
            int *childNode = *(int **)((int)parentNode + 8); // parent+0x08: first child
            char childActive = *(char *)((int)childNode + 0x15);

            while (childActive == '\0') {
                // Traverse to next sibling/child? This loop moves along the child chain.
                childActive = *(char *)(*(int *)((int)childNode + 8) + 0x15);
                parentNode = childNode;
                childNode = *(int **)((int)childNode + 8); // child+0x08: next in chain
            }

            // Set current to the node that had an active child (the one before the active one).
            *(int *)(this + 4) = (int)parentNode;
            return;
        }

        // Parent is active, but current is inactive. Move to next sibling.
        currentNode = *(int **)((int)currentNode + 4); // node+0x04: next sibling
        char siblingActive = *(char *)((int)currentNode + 0x15);

        while ((siblingActive == '\0') && (*(int *)(this + 4) == *currentNode)) {
            // Traverse siblings until an active one is found or we loop back.
            *(int *)(this + 4) = (int)currentNode;
            currentNode = *(int **)((int)currentNode + 4); // next sibling
            siblingActive = *(char *)((int)currentNode + 0x15);
        }

        if (*(char *)(*(int *)(this + 4) + 0x15) != '\0') {
            FUN_00b97aea(); // assertion: should not have active at stored position
            return;
        }

        // Update current node pointer to the newly found sibling.
        *(int *)(this + 4) = (int)currentNode;
    }
    else {
        // Current node is active. Move to its first child (or sibling if no child?).
        int *childNode = (int *)*(int *)((int)currentNode + 8); // node+0x08: first child
        *(int *)(this + 4) = (int)childNode;
        if (*(char *)((int)childNode + 0x15) != '\0') {
            FUN_00b97aea(); // assertion: child should be inactive here
            return;
        }
    }

    return;
}