// FUNC_NAME: TreeIterator::advanceToNextActive
void __thiscall TreeIterator::advanceToNextActive()
{
    // Check if tree root is valid
    if (*(int*)this == 0) {
        // error (likely assert)
        FUN_00b97aea();
    }

    int* currentNode = *(int**)(this + 4); // current pointer at +0x4

    if (*(char*)((int)currentNode + 0x15) == '\0') {
        // Current node is not active; traverse left subtree to find next active
        int* node = (int*)*currentNode; // left child at +0x0

        if (*(char*)(node + 0x15) == '\0') {
            // Go down left children until we find an active node
            char activeFlag = *(char*)(*(int*)(node + 8) + 0x15); // right child's active flag
            int* nextNode = (int*)(node + 8);
            while (activeFlag == '\0') {
                node = nextNode;
                nextNode = *(int**)((int)nextNode + 8);
                activeFlag = *(char*)((int)nextNode + 0x15);
            }
            *(int**)(this + 4) = node;
            return;
        }

        // Current not active but left child is active? Actually the code then goes to parent
        currentNode = (int*)currentNode[1]; // parent at +0x4
        char activeFlag = *(char*)((int)currentNode + 0x15);

        while (activeFlag == '\0' && *(int*)(this + 4) == *currentNode) {
            // Parent not active and previous current was left child of this parent (via offset 0)
            *(int*)(this + 4) = (int)currentNode;
            currentNode = (int*)currentNode[1]; // go up to grandparent
            activeFlag = *(char*)((int)currentNode + 0x15);
        }

        if (*(char*)(*(int*)(this + 4) + 0x15) != '\0') {
            // Should not happen; new current active? error
            FUN_00b97aea();
            return;
        }
        *(int*)(this + 4) = (int)currentNode;
    } else {
        // Current node is active; move to its right child
        int* rightChild = (int*)currentNode[2]; // right child at +0x8
        *(int*)(this + 4) = (int)rightChild;
        if (*(char*)((int)rightChild + 0x15) != '\0') {
            // Right child is active? error
            FUN_00b97aea();
            return;
        }
    }
    return;
}