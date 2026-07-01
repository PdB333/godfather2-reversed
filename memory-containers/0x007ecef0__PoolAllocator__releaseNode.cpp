// FUNC_NAME: PoolAllocator::releaseNode
// Address: 0x007ecef0
// Role: Removes a node from a container's doubly linked list, calls destructor, and frees memory via the allocator's virtual deallocation function.
// The node must not be the container's sentinel head (at container+0x18).
// Outputs an iterator (container + next node pointer) to allow caller to continue iteration.

void __thiscall PoolAllocator::releaseNode(int* outIterator, Container* container, ListNode* node)
{
    int* nextNode;

    // Validate arguments: container and node must be non-null; node must not be the container's sentinel head
    if (container == nullptr) {
        assertionFailed();
    }
    if (node == *(ListNode**) (container + 0x18)) {   // +0x18: sentinel head pointer
        assertionFailed();
    }

    nextNode = node->next;   // save next pointer before unlinking

    // Remove node from the list only if it is not the allocator's own head (sentinel of the free/used list)
    // Note: allocator's head is at this[6] (offset 0x18)
    if (node != (ListNode*) this->head) {   // this+0x18 (this[6]) is the allocator's list head
        // Unlink node from the doubly linked list
        node->prev->next = nextNode;        // node->prev[0] = node->next
        nextNode->prev = node->prev;        // node->next + 4 = node->prev

        // Call node destructor
        nodeDestructor(node);

        // Deallocate node memory via allocator's virtual function (vtable+4)
        (this->vtable->deallocate)(node, 0x24);   // size 0x24 = 36 bytes

        // Decrement the count of allocated nodes
        this->count--;   // this+0x1C (this[7])
    }

    // Build output iterator: (container, next node)
    outIterator[0] = (int) container;
    outIterator[1] = (int) nextNode;
}