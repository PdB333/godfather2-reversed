// FUNC_NAME: LinkedListNode::destructor (unlink and cleanup)
// Address: 0x007a0560
// This function appears to be a destructor for a doubly-linked list node.
// It unlinks the node from its list, performs cleanup, and optionally deallocates memory.

int __thiscall LinkedListNode::destructor(byte deallocFlag) {
    // Set vtable pointer at offset +0x28 to static base vtable
    *(void***)(this + 0x28) = &PTR_LAB_00e317cc;

    // Linked list pointers at offsets:
    // +0x18: previous node pointer
    // +0x1c: next node pointer
    // +0x20: data pointer (the actual object stored in the list)
    LinkedListNode* prev = *(LinkedListNode**)(this + 0x18);
    LinkedListNode* next = *(LinkedListNode**)(this + 0x1c);
    void* data = *(void**)(this + 0x20);

    // Unlink this node from the list, bypassing it and connecting neighbors directly to data
    if (prev != 0) {
        if (next == 0) {
            // No next node: set prev's next (offset +4 in prev) to data
            *(void**)((int)prev + 4) = data;
        } else {
            // Next exists: set next's prev (offset +8 in next) to data
            *(void**)((int)next + 8) = data;
        }
        if (data != 0) {
            // Set data's prev (offset +4 in data) to next
            *(void**)((int)data + 4) = next;
        }
    }

    // Call cleanup function (likely destructor of base class or internal resources)
    FUN_0064d150();

    // If the low bit of deallocFlag is set, free memory
    if ((deallocFlag & 1) != 0) {
        FUN_009c8eb0(this); // operator delete
    }

    return (int)this;
}