// FUN_0045df20: EARSObjectManager::destroyAllNodes

struct EARSObjectNode {
    // +0x10c: pointer to a child object that must be released
    void* childObject;
    // +0x124: next node in the linked list
    EARSObjectNode* next;
    // other fields...
};

struct EARSObjectManager {
    // +0x218: head of the linked list of nodes
    EARSObjectNode* head;
    // other fields...
};

void EARSObjectManager::destroyAllNodes() {
    EARSObjectNode* currentNode = this->head;
    if (currentNode == nullptr) {
        return;
    }

    // Release the head node (reference count decrement)
    SafeRelease(&currentNode);
    ContextSwitch(); // yield or check for interrupts

    // Traverse the list
    EARSObjectNode* nextNode = currentNode->next; // +0x124
    while (nextNode != nullptr) {
        currentNode = nextNode;
        SafeRelease(&currentNode);

        // Destroy the child object if one exists
        void* child = currentNode->childObject; // +0x10c
        if (child != nullptr) {
            DestroyChildObject(child);
            // Call vtable+4 to deallocate child+8 and child itself
            MemoryAllocator* alloc = GetMemoryAllocator();
            (*(void(__thiscall**)(void*, int))(*alloc + 4))((char*)child + 8, 0);
            (*(void(__thiscall**)(void*, int))(*alloc + 4))(child, 0);
            currentNode->childObject = nullptr;
        }

        ContextSwitch();

        nextNode = currentNode->next; // +0x124

        // Deallocate the node itself using the allocator
        alloc = GetMemoryAllocator();
        (*(void(__thiscall**)(void*, int))(*alloc + 4))(currentNode, 0);
    }

    // Finalize the manager state
    this->clear();  // calls FUN_00518ff0

    // Free the original head pointer
    MemoryAllocator* alloc = GetMemoryAllocator();
    (*(void(__thiscall**)(void*, int))(*alloc + 4))(this->head, 0);
    this->head = nullptr;
}