// FUNC_NAME: TreeIterator::advance
// Function at 0x008ea280: Advances the iterator to the next active node in a binary tree.
// Node structure offsets:
//   +0x00: left child pointer (int*)
//   +0x04: right child pointer (int*)
//   +0x08: parent pointer? (unused here)
//   +0x19: active flag (char, 0 = inactive, non-zero = active)
// Iterator structure:
//   +0x00: root pointer (int*)
//   +0x04: current node pointer (int*)

void __thiscall TreeIterator::advance(int *this)
{
    char activeFlag;
    int *currentNode;
    int *nodePtr;
    int *tempPtr;

    if (this[0] == 0) {
        // Root is null, error
        FUN_00b97aea(); // likely assertion failure
    }

    currentNode = (int *)this[1];
    activeFlag = *(char *)((int)currentNode + 0x19);

    if (activeFlag == '\0') {
        // Current node is inactive, find next active node
        nodePtr = (int *)currentNode[2]; // right child (offset +0x08)
        if (*(char *)((int)nodePtr + 0x19) != '\0') {
            // Right child is active, go to its leftmost descendant
            currentNode = (int *)currentNode[1]; // left child (offset +0x04)
            activeFlag = *(char *)((int)currentNode + 0x19hed);
            while (activeFlag == '\0' && this[1] == currentNode[2]) {
                // While current node is inactive and it is the right child of its parent
                this[1] = (int)currentNode;
                currentNode = (int *)currentNode[1]; // move to left child
                activeFlag = *(char *)((int)currentNode + 0x19);
            }
            this[1] = (int)currentNode;
            return;
        }
        // Right child is inactive, go up to parent
        activeFlag = *(char *)(*nodePtr + 0x19); // flag of node pointed by right child's first field? (likely parent)
        tempPtr = (int *)*nodePtr;
        while (activeFlag == '\0') {
            activeFlag = *(char *)(*tempPtr + 0x19);
            nodePtr = tempPtr;
            tempPtr = (int *)*tempPtr;
        }
        this[1] = (int)nodePtr;
        return;
    }
    // Current node is active, error (should not happen)
    FUN_00b97aea();
    return;
}