// FUNC_NAME: LinkedListNode::~LinkedListNode
int __thiscall LinkedListNode::~LinkedListNode(void* this, byte flags) {
    // +0x28: vtable pointer for base1
    *(void***)((int)this + 0x28) = &PTR_LAB_00e35c24;
    // +0x38: vtable pointer for base2
    *(void***)((int)this + 0x38) = &PTR_LAB_00e317cc;
    
    // Unlink this node from the doubly linked list
    // Offsets: +0x18 = next, +0x1c = prev, +0x20 = some data/owner pointer
    int next = *(int*)((int)this + 0x18);
    if (next != 0) {
        int prev = *(int*)((int)this + 0x1c);
        int data = *(int*)((int)this + 0x20);
        if (prev == 0) {
            // If this node is the head, update the next node's prev pointer (offset +4 in next)
            *(int*)(next + 4) = data;
        } else {
            // Otherwise update the previous node's next pointer (offset +8 in prev)
            *(int*)(prev + 8) = data;
        }
        if (data != 0) {
            // Update the data node's prev pointer (offset +4 in data)
            *(int*)(data + 4) = prev;
        }
    }
    
    // Call internal cleanup/release function
    FUN_0064d150();
    
    // If the destroy flag is set, release memory
    if ((flags & 1) != 0) {
        FUN_009c8eb0((int)this);
    }
    return (int)this;
}