// FUNC_NAME: NodeIterator::findNextActive
// Address: 0x005e09e0
// This function traverses a tree structure (with parent/next sibling/child pointers) to find the next node with a non-zero flag at offset 0x15.
// Context struct: this[0] = initFlag, this[4] = current node pointer.
// Node offsets: +0x0 = firstChild, +0x4 = nextSibling, +0x8 = parent, +0x15 = active flag (bool).

void NodeIterator::findNextActive(void)
{
    char activeFlag;
    int nodePtr;
    int *parentNode;
    int *childNode;
    int *thisPtr; // ESI

    // If the tree is not initialized, call initializer.
    if (*thisPtr == 0) {
        initTree(); // 0x00b97aea
    }

    nodePtr = thisPtr[1]; // current node pointer
    // Check if current node's active flag is zero
    if (*(char *)(nodePtr + 0x15) == '\0') {
        // Get parent node (offset +0x8)
        parentNode = *(int **)(nodePtr + 8);
        // If parent is active, traverse to next sibling
        if (*(char *)((int)parentNode + 0x15) != '\0') {
            // Move to next sibling (offset +0x4)
            nodePtr = *(int *)(nodePtr + 4);
            activeFlag = *(char *)(nodePtr + 0x15);
            // While the sibling is inactive and its parent matches the original current node
            while ((activeFlag == '\0') && (thisPtr[1] == *(int *)(nodePtr + 8))) {
                thisPtr[1] = nodePtr; // update current to sibling
                nodePtr = *(int *)(nodePtr + 4); // next sibling
                activeFlag = *(char *)(nodePtr + 0x15);
            }
            thisPtr[1] = nodePtr; // set current to the found active sibling
            return;
        }
        // Parent is inactive: traverse down through firstChild chain
        activeFlag = *(char *)(*parentNode + 0x15); // firstChild's active flag
        childNode = (int *)*parentNode; // firstChild pointer
        while (activeFlag == '\0') {
            activeFlag = *(char *)(*childNode + 0x15); // go deeper via child's firstChild
            parentNode = childNode;
            childNode = (int *)*childNode;
        }
        thisPtr[1] = (int)parentNode; // set current to the parent of the last inactive child
        return;
    }
    // Current node is active: call initializer (potentially error or reset)
    initTree();
    return;
}