// FUNC_NAME: NodeIterator::advanceNextValid
// Function at 0x004cab50: Advances the iterator to the next valid node in a tree structure.
// Node structure offsets:
// +0x00: pointer to first child (Node*)
// +0x04: pointer to next sibling (Node*)
// +0x08: pointer to parent (Node*)
// +0x15: boolean flag (valid? 1=valid, 0=invalid)
// Iterator structure offsets:
// +0x00: pointer to root sentinel (Node*)
// +0x04: pointer to current node (Node*)

void __thiscall NodeIterator::advanceNextValid() {
    char flag;
    Node* nextNode; // iVar2
    Node* parentNode; // piVar3
    Node* childNode; // piVar4

    // Ensure root is valid
    if (this->root == nullptr) {
        assertionFailure(); // FUN_00b97aea
    }

    nextNode = this->current;
    // Only proceed if current node is invalid (flag == 0)
    if (nextNode->flag == '\0') {
        parentNode = nextNode->parent; // +0x08

        // If parent is valid, move to next sibling looking for a valid node
        if (parentNode->flag != '\0') {
            // Start from current's next sibling
            nextNode = this->current->nextSibling; // +0x04
            flag = nextNode->flag;
            // Continue moving to next sibling as long as current node is invalid
            // and the next sibling's parent is the original current node (i.e., still in same subtree?)
            while ((flag == '\0') && (this->current == nextNode->parent)) {
                this->current = nextNode;
                nextNode = nextNode->nextSibling;
                flag = nextNode->flag;
            }
            this->current = nextNode;
            return;
        }

        // If parent is invalid, traverse down the leftmost children until a valid node is found
        // Start from parent's first child
        childNode = parentNode->firstChild; // +0x00
        flag = childNode->flag;
        while (flag == '\0') {
            // Move to the next child (dereference childNode as pointer to first child of that node)
            flag = childNode->firstChild->flag; // *(byte*)(*(int*)childNode+0x15)
            childNode = childNode->firstChild; // *(int*)childNode
        }
        // Set current to the node just before the found valid node (the one with flag==0)
        this->current = childNode; // Actually childNode was updated, but loop stores previous in childNode? The assembly suggests childNode is reassigned; after loop, childNode points to a node with flag!=0? Need careful.
        return;
    }

    // If current node is already valid, assertion fails (this function should only be called on invalid nodes)
    assertionFailure();
}