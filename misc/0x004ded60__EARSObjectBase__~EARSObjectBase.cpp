// FUNC_NAME: EARSObjectBase::~EARSObjectBase
void __thiscall EARSObjectBase::~EARSObjectBase()
{
    // Set vtable to base destructor thunk (likely no-op)
    this->vtable = &PTR_FUN_00e36f74;

    // Clean up listener/iterator data structure
    // param_1[5] and param_1[6] hold current iteration index and a second value
    if (this->listenerCurrent != 0) {
        // Access thread-local storage base (FS segment, offset 0x2c)
        // This is typical for exception handling or TLS
        int* tlsBase = *(int**)(__readfsdword(0x2c) + 0x2c);
        int current = this->listenerCurrent;    // offset +0x14
        int value = this->listenerValue;        // offset +0x18
        do {
            // Read next entry from an array stored in TLS
            int next = *(int*)(tlsBase[2] + current);
            int nextValue = *(int*)(tlsBase[2] + 4 + current);
            // Cleanup listener (likely remove from active list)
            cleanupListener(current, value);
            // Process any pending cleanup actions
            processCleanup();
            current = next;
            value = nextValue;
        } while (current != 0);
    }

    // Destroy all child objects stored in a doubly-linked list
    // param_1[4] is head of the list
    ChildNode* node = this->childListHead;      // offset +0x10
    while (node != nullptr) {
        ChildNode* nextNode = node->next;       // offset +0xC4 (0x31*4)
        if (node == this->childListHead) {
            this->childListHead = nextNode;
            if (nextNode != nullptr) {
                nextNode->prev = nullptr;       // offset +0xC8 (0x32*4)
            }
        } else {
            if (node->prev != nullptr) {
                node->prev->next = nextNode;
            }
            if (nextNode != nullptr) {
                nextNode->prev = node->prev;
            }
        }
        // Call virtual destructor on child with argument 1 (delete semantics)
        (*(void(__thiscall**)(ChildNode*, int))node->vtable)(node, 1);
        node = nextNode;
    }

    // Free an allocator-managed resource if present
    // param_1[3] is a pointer to some allocated block
    if (this->allocatorBlock != nullptr) {      // offset +0x0C
        MemoryManager* mgr = FUN_009c8f80();    // get singleton
        // Call free via vtable+4 (2nd virtual function)
        (*(void(__thiscall**)(MemoryManager*, void*, int))mgr->vtable)(mgr, this->allocatorBlock, 0);
        this->allocatorBlock = nullptr;
    }
}