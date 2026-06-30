// FUNC_NAME: LinkedList::removeNode
// Function address: 0x00610100
// Role: Removes a node from a doubly-linked list. The container (this) stores the head of the list at +0x84.
// Each node has a next pointer at +0x88, a previous pointer at +0x8C, and an owner/list pointer at +0x80.
void __thiscall LinkedList::removeNode(void* container, void* node)
{
    void* next = *(void**)((char*)node + 0x88);   // +0x88: next node
    void* prev = *(void**)((char*)node + 0x8C);   // +0x8C: previous node

    // Unlink the node from its neighbors
    if (next != nullptr) {
        *(void**)((char*)next + 0x8C) = prev;     // update next's prev to point to our prev
    }
    if (prev != nullptr) {
        *(void**)((char*)prev + 0x88) = next;     // update prev's next to point to our next
    }

    // If this node was the head of the list, advance the head to the next node
    if (*(void**)((char*)container + 0x84) == node) {
        *(void**)((char*)container + 0x84) = next;
    }

    // Clear the node's own pointers to mark it as removed
    *(void**)((char*)node + 0x8C) = nullptr;      // prev
    *(void**)((char*)node + 0x88) = nullptr;      // next
    *(void**)((char*)node + 0x80) = nullptr;      // owner/list reference
}