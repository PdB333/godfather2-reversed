// FUNC_NAME: ObjectList::extractNode

struct ObjectNode {
    void** vtable;       // +0x00
    // ... other fields ...
    ObjectNode* prev;    // +0x40
    ObjectNode* next;    // +0x44
    int cleanupFlag;     // +0xD0
};

struct ObjectList {
    // ... other fields ...
    ObjectNode* currentNode;  // +0x20
    ObjectNode* sentinel;     // +0x28
};

// Removes the current node from the doubly linked list.
// Returns the removed node, or nullptr if currentNode == sentinel.
ObjectNode* ObjectList::extractNode() {
    if (this->currentNode != this->sentinel) {
        // Unlink the node
        this->currentNode->next->prev = this->currentNode->prev;
        this->currentNode->prev->next = this->currentNode->next;

        // If cleanup flag is set, perform cleanup and clear it
        if (this->currentNode->cleanupFlag) {
            FUN_0066dfe0();  // cleanup function
            this->currentNode->cleanupFlag = 0;
        }

        // Call the node's second virtual function (likely destructor/finalizer)
        ((void (*)(void))(this->currentNode->vtable[1]))();

        return this->currentNode;
    }
    return nullptr;
}