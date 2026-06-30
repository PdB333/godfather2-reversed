// FUNC_NAME: LinkedListNode::destroy
void __thiscall LinkedListNode::destroy(void) {
    char deallocResult;
    LinkedListNode* prev;
    LinkedListNode* next;
    void* object;

    prev = this->prev;   // +0x1c
    next = this->next;   // +0x20

    // Unlink from doubly-linked list
    if (prev != NULL) {
        prev->next = next;   // prev + 0x20
    }
    if (next != NULL) {
        next->prev = prev;   // next + 0x1c
    }

    // If the node holds an object, clear its back-reference and destroy it
    object = this->object;   // +0x00
    if (object != NULL) {
        *(uint32_t*)((uint8_t*)object + 0x30) = 0;
        if (object != NULL) {
            // Call virtual destructor (vtable+4)
            (**(void (__thiscall***)(void*))object)(object);
        }
    }

    this->object = NULL;

    deallocResult = nodePoolDeallocate(this);  // FUN_005c43d0
    if (deallocResult == '\0') {
        // Error handler: call global crash/abort function
        (**(void (__thiscall***)(void))(**(uint32_t**)(DAT_012234ec + 4) + 4))();
    }
}