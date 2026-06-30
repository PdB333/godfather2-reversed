// FUNC_NAME: NodePool::removeNodeFromList

// Function at 0x00440e30: Removes a node from a doubly-linked list and optionally frees it.
// The pool (this) manages memory for nodes; listOwner is the container whose list head is at +0x18.
// outResult receives (listOwner, node->next) after removal.
void NodePool::removeNodeFromList(int **outResult, void *listOwner, Node *node)
{
    // Assertions
    if (listOwner == nullptr) {
        assertionFailure(); // FUN_00b97aea
    }
    if (node == *(Node **)((char *)listOwner + 0x18)) {
        assertionFailure(); // Cannot remove the head node itself
    }

    Node *next = (Node *)node->next; // Save original next pointer (offset +0x00)

    // Check if node is the pool's free list head (offset +0x18 in pool)
    if (node != *(Node **)((char *)this + 0x18)) {
        // Remove from double linked list
        // node->prev->next = node->next
        *(Node **)node->prev = next;
        // node->next->prev = node->prev
        *(Node **)((char *)next + 4) = (Node *)node->prev;

        // Free any sub-items (count at offset +0x12, sub-item array at +0x0C)
        while (*(short *)((char *)node + 0x12) != 0) {
            freeSubItem((void *)((char *)node + 0x0C)); // FUN_00408310
        }

        // Call destructor via vtable at +0x04 of the pool? Actually it's pool->vtable[1](node,size)
        (**(void (__thiscall **)(void *, void *, int))(*((int *)this) + 4))(node, this, 0x20); // vtable+4 = destructor/delete

        // Decrease pool's count (offset +0x1C)
        ((int *)this)[7]--;
    }

    // Output: listOwner and the original next pointer
    outResult[0] = (int)listOwner;
    outResult[1] = (int)next;
}