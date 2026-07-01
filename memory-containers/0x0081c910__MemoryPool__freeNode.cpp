// FUNC_NAME: MemoryPool::freeNode
// Address: 0x0081c910
// This function removes a node from the free list, destroys it, and updates the pool's allocated count.
// Parameters:
//   this (param_1) - MemoryPool instance
//   out (param_2) - output struct receiving containerId and old next pointer
//   containerId (param_3) - identifier of the free list (pointer to head sentinel)
//   node (param_4) - node to be freed
void __thiscall MemoryPool::freeNode(undefined4 *this, int *out, int containerId, int *node)
{
    int oldNext;
    
    // Assertions: container must exist and node cannot be the sentinel head
    if (containerId == 0) {
        assertionFail(); // FUN_00b97aea
    }
    if (node == *(int **)(containerId + 0x18)) {
        assertionFail(); // node is the sentinel head of the free list
    }
    
    oldNext = *node; // node->next at offset 0x00
    
    // If the node is not the special "current" pointer stored at this+0x18 (param_1[6])
    if (node != (int *)this[6]) {
        // Unlink the node from its current doubly linked list
        *(int *)node[1] = oldNext;        // node->prev->next = node->next
        *(int *)(oldNext + 4) = node[1];  // node->next->prev = node->prev
        
        // Clear node contents (likely memset to zero)
        resetNode(node); // FUN_0081c4d0
        
        // Call virtual destructor at vtable+4 with size hint 0x2c (44 bytes)
        (**(code **)(*(int *)*this + 4))(node, 0x2c);
        
        // Decrement allocated node count
        this[7] = this[7] - 1; // m_allocatedCount--
    }
    
    // Output container ID and old next pointer (for caller's iterator update)
    out[0] = containerId;
    out[1] = oldNext;
    return;
}