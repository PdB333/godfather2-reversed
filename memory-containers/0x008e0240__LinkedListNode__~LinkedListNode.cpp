// FUNC_NAME: LinkedListNode::~LinkedListNode
int __thiscall LinkedListNode::~LinkedListNode(void* this, byte flags) {
    // Set vtable to static address to prevent further virtual calls during destruction
    *(void***)((int)this + 0x28) = &PTR_LAB_00e317cc;

    // Unlink node from the doubly linked list structure
    // Offsets: +0x18 = next, +0x1c = prev, +0x20 = data (possibly a head pointer or payload)
    void* pNext = *(void**)((int)this + 0x18);
    if (pNext != nullptr) {
        void* pPrev = *(void**)((int)this + 0x1c);
        void* pData = *(void**)((int)this + 0x20);
        if (pPrev == nullptr) {
            // Node is the first in the list; update the next node's backward link to the data
            *(void**)((int)pNext + 4) = pData;
        } else {
            // Node is not the first; update the previous node's forward link to the data
            *(void**)((int)pPrev + 8) = pData;
        }
        if (pData != nullptr) {
            // If the data pointer is valid, update its backward link to the previous node
            *(void**)((int)pData + 4) = pPrev;
        }
    }

    // Call base destructor or cleanup routine
    FUN_0064d150();

    // If the lowest bit of flags is set, free the memory
    if ((flags & 1) != 0) {
        FUN_009c8eb0(this);
    }

    return (int)this;
}