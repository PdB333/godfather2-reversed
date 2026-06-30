// FUNC_NAME: TreeIterator::advance
// Address: 0x005e09e0
// Role: Advances the iterator to the next active node in a tree/linked structure.
// The structure at this has two fields: root (offset 0) and current (offset 4).
// Nodes have layout: left (0x00), right (0x04), parent (0x08), active (0x15 char).

void __thiscall TreeIterator::advance(void) {
    char activeFlag;
    int *nodePtr;
    int *otherNode;
    int *tempNode;
    int *thisCurrent;

    // If root is null, initialize (likely resets iterator)
    if (*(int *)this == 0) {
        FUN_00b97aea(); // init / reset
    }

    nodePtr = *(int **)(this + 4); // current
    activeFlag = *(char *)((int)nodePtr + 0x15); // node->active

    if (activeFlag == '\0') {
        otherNode = *(int **)((int)nodePtr + 8); // node->parent

        if (*(char *)((int)otherNode + 0x15) != '\0') { // parent is active
            // Start from node->right (sibling?) and walk rightwards
            nodePtr = *(int **)((int)nodePtr + 4); // node->right
            activeFlag = *(char *)((int)nodePtr + 0x15);
            while (activeFlag == '\0' && *(int *)(this + 4) == *(int *)((int)nodePtr + 8)) {
                *(int *)(this + 4) = (int)nodePtr;
                nodePtr = *(int **)((int)nodePtr + 4); // next right
                activeFlag = *(char *)((int)nodePtr + 0x15);
            }
            *(int *)(this + 4) = (int)nodePtr;
            return;
        } else {
            // Walk leftwards from parent's left child
            tempNode = *(int **)((int)otherNode); // parent->left
            // Since otherNode was at node->parent, dereferencing gets parent->left
            activeFlag = *(char *)(*tempNode + 0x15); // left child's active
            while (activeFlag == '\0') {
                activeFlag = *(char *)(*tempNode + 0x15); // walk left? This seems to follow left pointers
                tempNode = (int *)*tempNode;
            }
            *(int *)(this + 4) = (int)tempNode;
            return;
        }
    } else {
        // Current node is active – this case shouldn't happen for an advance?
        FUN_00b97aea(); // reset or error
        return;
    }
}