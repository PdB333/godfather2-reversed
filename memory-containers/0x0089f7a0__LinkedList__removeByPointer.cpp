// FUNC_NAME: LinkedList::removeByPointer
// Function address: 0x0089f7a0
// Role: Removes a node from a circular doubly linked list by matching a stored pointer (key).
// The list uses a sentinel node (this). Each node contains next, prev, and a data pointer.
// If the data pointer is non-null, a destructor (FUN_004daf90) is called on it.
// Then the node memory is freed via FUN_009c8f10.

struct ListNode {
    ListNode* next;   // +0x00
    ListNode* prev;   // +0x04
    void* data;       // +0x08 (stored as int in decompiled code)
};

// External functions (likely from engine)
extern void __cdecl destroyDataObject(void* data); // FUN_004daf90
extern void __cdecl freeNode(ListNode* node);      // FUN_009c8f10

void __thiscall LinkedList::removeByPointer(void** keyPtr) {
    // keyPtr is a pointer to the data pointer to match
    ListNode* current = this->next; // start from first real node
    while (current != this) {       // until we loop back to sentinel
        ListNode* nextNode = current->next; // save next before potential removal
        if (current->data == *keyPtr) {
            // Remove current node from list
            ListNode* prevNode = current->prev;
            ListNode* nextNode2 = current->next;
            prevNode->next = nextNode2;
            nextNode2->prev = prevNode;
            // Destroy the data object if it exists
            if (current->data != nullptr) {
                destroyDataObject(current->data);
            }
            // Free the node memory
            freeNode(current);
        }
        current = nextNode;
    }
}