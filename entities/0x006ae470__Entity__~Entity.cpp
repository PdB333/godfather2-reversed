// FUNC_NAME: Entity::~Entity
void __thiscall Entity::~Entity() {
    // +0x48: embedded linked list node (struct Node { int prevOrData; Node* next; })
    // +0x284: resource pointer (released via releaseResource)
    
    // Temporary vtable guard (points to base class vtable)
    void** vtableGuard = &PTR_FUN_00e31e2c; // Base vtable pointer

    // If this is non-null (passed via ecx? but param_1 is the this pointer, so always non-null if called)
    int thisPtr = reinterpret_cast<int>(this);
    if (thisPtr != 0) {
        // Get pointer to embedded node at +0x48
        Node* node = reinterpret_cast<Node*>(thisPtr + 0x48);
        
        // Save old next pointer
        Node* oldNext = node->next;
        
        // Self-reference next to indicate node is no longer in any list
        node->next = node; // Set next to itself (sentinel)
        
        // Resource at +0x284
        Resource* res = *reinterpret_cast<Resource**>(thisPtr + 0x284);
        
        // Release the resource
        releaseResource(&res, 0);
        
        // If node exists, destroy it
        if (node != nullptr) {
            deleteNode(&node); // Custom node deallocation
        }
    }
}