// FUNC_NAME: LinkedList::spliceNode
void __thiscall LinkedList::spliceNode(void* this, Node* node) {
    // node structure assumed: +0x00: container pointer (used as "owner" or magic), +0x04: prev, +0x08: next
    // this+0x04 points to a sentinel head node (or list descriptor) that holds tail pointer at +0x04

    Node* next = *(Node**)(node + 8); // node->next
    // Save node's original next, then set node->next = next->container (first field of next node)
    *(Node**)(node + 8) = *(Node**)next; // node->next = next->container

    // Check a flag at next+0x19 (likely "isSentinel" or "isTail")
    if (*(char*)(*(int*)next + 0x19) == '\0') { // if next is not tail node
        *(int*)(*(int*)next + 4) = (int)node;   // next->prev = node
    }

    // Set next's second field (next+0x04) to node's original prev
    ((int*)next)[1] = *(int*)(node + 4); // next->prev = node->prev

    // Determine if node is the tail-of-list (compared to tail pointer stored at (this+4)->(this+4))
    if (node == *(Node*)(*(int*)(this + 4) + 4)) {
        // node is the tail: set tail pointer to next
        *(Node**)(*(int*)(this + 4) + 4) = next;
        // Make next's first field point to node (circular back)
        *(Node**)next = node;
        *(Node**)(node + 4) = next; // node->prev = next
        return;
    }

    Node* prev = *(Node**)(node + 4); // node->prev
    if (node == *prev) {
        // node is the head (prev->container equals node)
        *prev = next;
        *(Node**)next = node;
        *(Node**)(node + 4) = next;
        return;
    }

    // General case: splice node between prev and next
    // Set prev->next (offset +0x08) to next
    *((int*)prev + 2) = (int)next; // prev->next = next
    *(Node**)next = node;          // next->container = node
    *(Node**)(node + 4) = next;    // node->prev = next
}