// FUNC_NAME: TreeIterator::advance
// Function at 0x005e15c0 - Advances an iterator to next node in a tree structure (likely RB tree successor)
// Offsets:
// +0x00: root pointer or flag (0 = empty tree)
// +0x04: current node pointer (iterator position)
// Node fields:
// +0x00: left child pointer
// +0x04: parent pointer
// +0x08: right child pointer
// +0x15: boolean flag (0 = node is "red" or invalid, 1 = "black" or marked)

void __thiscall advance() {
    char nodeFlag;
    int currNode;
    int* rightChildPtr;
    int* nodePtr;

    // If tree root is null, assert/throw
    if (this->m_root == 0) {
        assertionFailed(); // FUN_00b97aea
    }

    currNode = this->m_current; // Current position in iteration

    // If current node is not marked (e.g., red or invalid)
    if (*(char*)(currNode + 0x15) == '\0') {
        rightChildPtr = *(int**)(currNode + 8); // Get right child pointer

        // If right child exists and is valid (flag != 0)
        if (*(char*)((int)rightChildPtr + 0x15) != '\0') {
            // Move to parent of current node
            currNode = *(int*)(currNode + 4);
            nodeFlag = *(char*)(currNode + 0x15);

            // Climb up while parent is invalid and parent's right child == current
            while (nodeFlag == '\0' && (this->m_current == *(int*)(currNode + 8))) {
                this->m_current = currNode;
                currNode = *(int*)(currNode + 4);
                nodeFlag = *(char*)(currNode + 0x15);
            }
            this->m_current = currNode;
            return;
        }

        // If right child is null or invalid, traverse to leftmost descendant
        nodeFlag = *(char*)(*(int*)rightChildPtr + 0x15); // Dereference first field of right child node
        nodePtr = (int*)*(int*)rightChildPtr;             // Follow left child chain

        while (nodeFlag == '\0') {
            nodeFlag = *(char*)(*(int*)nodePtr + 0x15);
            nodePtr = (int*)*(int*)nodePtr;
        }
        this->m_current = (int)nodePtr;
        return;
    }

    // Current node is marked (valid) – should not happen in this context
    assertionFailed();
    return;
}