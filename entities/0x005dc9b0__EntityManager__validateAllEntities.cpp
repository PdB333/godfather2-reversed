// FUNC_NAME: EntityManager::validateAllEntities
bool EntityManager::validateAllEntities() {
    // this is the manager object
    // +0x8: pointer to the head node of a linked list
    Node* headNode = *(Node**)((char*)this + 8);
    bool hasInvalidEntity = false;

    if (headNode == nullptr) {
        hasInvalidEntity = true;
    } else {
        // List is circular. Get the address of the first node.
        // Structure at headNode+0x1c holds a pointer to the first node's address?
        // Actually, we interpret: headNode->firstNodePointer (offset +0x1c) points to a pointer that stores the current node.
        // But this is messy. More likely: headNode->next (offset +0x1c) is a pointer to the next node.
        // And the double dereference gets the value stored at the next node's +0x0? No.
        // Given the code, assume headNode+0x1c is a pointer to the current node being iterated.
        // iVar2 = **(int**)(headNode + 0x1c) means: read pointer at headNode+0x1c, then read the int at that address.
        // That int is used as a node address (iVar2).
        // So the pointer at headNode+0x1c points to an int that holds the current node address.
        Node* currentNode = *(Node**)(*(int**)((char*)headNode + 0x1c));
        while (true) {
            // Re-read the headNode's offset +0x1c (this is expected to be constant)
            Node* const headNodeFirst = *(Node**)((char*)headNode + 0x1c);
            // Assertion: headNode should not be null and should match this->head
            if ((headNode == nullptr) || (headNode != *(Node**)((char*)this + 8))) {
                assertionFailed();
            }
            if (currentNode == headNodeFirst) break;
            if (headNode == nullptr) {
                assertionFailed();
            }
            if (currentNode == headNode) {
                assertionFailed();
            }
            // Check if the node's +0x10 field is zero
            if (*(int*)((char*)currentNode + 0x10) == 0) {
                hasInvalidEntity = true;
                processInvalidNode(currentNode);
            } else {
                processValidNode(currentNode);
                processNodePost(currentNode);
            }
            // Advance to next node? The decompiled code does not show this, but it must be inside processNodePost
            // We assume processNodePost advances the currentNode pointer via the stored pointer at headNode+0x1c.
            currentNode = *(Node**)(*(int**)((char*)headNode + 0x1c));
        }
    }
    return !hasInvalidEntity;
}

// Helper functions assumed to be defined elsewhere
void assertionFailed() {
    // FUN_00b97aea - likely an assertion failure handler
}

void processValidNode(Node* node) {
    // FUN_005dd660 - process a node with non-zero +0x10 field
}

void processInvalidNode(Node* node) {
    // FUN_005e09e0 - handle node with zero +0x10 field
}

void processNodePost(Node* node) {
    // FUN_005e09e0 - additional processing after valid node
}