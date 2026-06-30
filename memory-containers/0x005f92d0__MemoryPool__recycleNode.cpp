// FUNC_NAME: MemoryPool::recycleNode
// Address: 0x005f92d0
// This function removes a node (param_3) from the internal list of this (MemoryPool),
// frees it via virtual destructor, and initializes a new node (param_1) as the head of the container (param_2).
// The container is assumed to have a sentinel node at the pointed address.
// Offsets: this+0x18 = head pointer, this+0x1C = count.

struct Node {
    Node* prev; // +0x00
    Node* next; // +0x04
};

struct Container {
    int unknown[6];   // +0x00 to +0x17
    Node* head;       // +0x18
    int count;        // +0x1C
};

void __thiscall MemoryPool::recycleNode(Node* newHead, Container* container, Node* oldHead)
{
    // Assertions (debug checks)
    if (container == nullptr) {
        FUN_00b97aea(); // likely abort/assert
    }
    if (oldHead == container->head) {
        FUN_00b97aea(); // assert: oldHead must be the container's head
    }

    Node* nextNode = oldHead->next; // save next pointer of old head

    // Remove oldHead from the pool's internal free list (if it's not the list's own head)
    if (oldHead != this->head) {
        // Unlink oldHead from its current list
        oldHead->prev->next = nextNode;
        nextNode->prev = oldHead->prev;

        // Call virtual destructor on oldHead with size 12 (deallocate)
        (*(void(__thiscall**)(Node*, uint))(*(uint*)this + 4))(oldHead, 12);
        this->count--;
    }

    // Initialize newHead with the container and the saved next pointer
    newHead->prev = container;      // point back to container (sentinel)
    newHead->next = nextNode;       // point to the original second node
}