// FUNC_NAME: ListNode::destroy
// Address: 0x0089bda0 - Destroys a node by unlinking it from a doubly-linked list and optionally freeing memory.
// The node structure uses intrusive list pointers at offsets:
// +0x18: pointer to previous node (prev)
// +0x1c: pointer to next node (next)
// +0x20: pointer to the node itself (self, used for consistency checks)
// +0x28: vtable pointer (set to a specific vtable during destruction)

class ListNode {
public:
    void setVtable(void *vtable);
    void cleanup(); // placeholder for FUN_0064d150
    void freeNode(void *ptr); // placeholder for FUN_009c8eb0 (operator delete or custom deallocator)

    int destroy(byte deleteFlag) {
        // Set vtable to the designated vtable for this node type
        *(void***)(this + 0x28) = &PTR_LAB_00e317cc;

        // Unlink the node from the intrusive doubly-linked list
        if (*(int*)(this + 0x18) != 0) { // prev exists
            if (*(int*)(this + 0x1c) == 0) { // no next node
                // Write self pointer into the previous node's "next" field (offset +4)
                *(int*)(*(int*)(this + 0x18) + 4) = *(int*)(this + 0x20);
            } else { // both prev and next exist
                // Write self pointer into the next node's "prev" field (offset +8)
                *(int*)(*(int*)(this + 0x1c) + 8) = *(int*)(this + 0x20);
            }
            // If self pointer is valid, update its "next" pointer (offset +4) to point to the next node
            if (*(int*)(this + 0x20) != 0) {
                *(int*)(*(int*)(this + 0x20) + 4) = *(int*)(this + 0x1c);
            }
        }

        // Perform class-specific cleanup (likely virtual or overridable)
        cleanup();

        // If the low bit of deleteFlag is set, free the memory
        if (deleteFlag & 1) {
            freeNode(this);
        }

        return this;
    }
};