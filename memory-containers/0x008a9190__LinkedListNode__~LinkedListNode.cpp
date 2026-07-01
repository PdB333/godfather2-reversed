// FUNC_NAME: LinkedListNode::~LinkedListNode

int __thiscall LinkedListNode::~LinkedListNode(byte freeMemory) {
    // Set vtable to base class vtable (0x00e317cc)
    *(void***)(this + 0x28) = &PTR_LAB_00e317cc;

    // Get linked list pointers (offsets: +0x18 next, +0x1c prev, +0x20 data)
    void* next = *(void**)(this + 0x18);
    void* prev = *(void**)(this + 0x1c);
    void* data = *(void**)(this + 0x20);

    // Unlink this node from the doubly linked list
    if (next) {
        if (prev) {
            // Update prev->next (offset +0x8) to data
            *(void**)((int)prev + 8) = data;
        } else {
            // Update next->prev (offset +0x4) to data
            *(void**)((int)next + 4) = data;
        }
        if (data) {
            // Update data->back (offset +0x4) to prev
            *(void**)((int)data + 4) = prev;
        }
    }

    // Call base class destructor
    FUN_0064d150();

    // Free memory if requested (bit 0 of freeMemory)
    if (freeMemory & 1) {
        FUN_009c8eb0(this);
    }

    return this;
}