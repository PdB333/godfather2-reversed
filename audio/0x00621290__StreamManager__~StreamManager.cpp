// FUNC_NAME: StreamManager::~StreamManager

void __fastcall StreamManager::~StreamManager(StreamManager* this)
{
    int* node;

    // Set vtable pointer to derived class vtable (or base class vtable)
    this->vtable = &PTR_FUN_00e414d8;

    // Call base class destructor or cleanup function
    FUN_00621390();

    // Free the linked list of streams (offset +0x10)
    node = this->streamList; // +0x10
    if (node != 0) {
        // Remove node from list and free it
        FUN_00621750();
        FUN_009c8eb0(node); // free memory
        this->streamList = 0;
    }

    // Free the second list (offset +0x0C)
    node = this->secondList; // +0x0C
    if (node != 0) {
        // Unlink node from doubly linked list
        // node->next->prev = node->prev; (typical doubly linked list removal)
        // Offsets: node+0x1c = next, node+0x20 = prev? Actually unclear.
        FUN_006227f0(*(int*)(*(int*)(node + 0x1c) + 4));
        *(int*)(*(int*)(node + 0x1c) + 4) = *(int*)(node + 0x1c);
        *(int*)(node + 0x20) = 0;
        *(int*)*(int*)(node + 0x1c) = *(int*)(node + 0x1c);
        *(int*)(*(int*)(node + 0x1c) + 8) = *(int*)(node + 0x1c);

        node = this->secondList;
        if (node != 0) {
            FUN_00621ca0();
            FUN_009c8eb0(node);
        }
        this->secondList = 0;
    }

    // Call virtual method on member at offset +0x04 (likely a subclass)
    (*(void (**)(void))(*(int*)this->member1 + 0xC))(); // +0x04
    // Call virtual method on member at offset +0x18 (likely another subclass)
    (*(void (**)(void))(*(int*)this->member6 + 0xC))(); // +0x18

    // Free memory at offset +0x1C
    FUN_009c8f10(this->member7); // +0x1C

    // Reset vtable to base class vtable (or sentinel)
    this->vtable = &PTR_LAB_00e414dc;

    // Clear global singleton flag
    DAT_012234ac = 0;

    return;
}