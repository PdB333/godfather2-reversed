// FUNC_NAME: EARSLinkedList::removeHead
// Function address: 0x0060d1d0
// Removes the head node from a doubly linked list, updates head/tail, and decrements count.
// Node structure: +0x00: data, +0x04: next, +0x08: prev
// Global static members: head (0x012224ac), tail (0x012224b0), count (0x012224b4), vtablePtr (0x012224bc)

void EARSLinkedList::removeHead(int** headPtr, int** outputNewHeadPtr)
{
    int* node = *headPtr;
    int* nextNode = nullptr;
    if (node != nullptr) {
        nextNode = (int*)*(int*)(node + 4); // node->next
    }
    *headPtr = nextNode; // update head to next

    if (node == EARSLinkedList::head) {
        if (node == EARSLinkedList::tail) {
            // List becomes empty
            EARSLinkedList::tail = nullptr;
            EARSLinkedList::head = nullptr;
        } else {
            EARSLinkedList::head = nextNode;
            if (nextNode != nullptr) {
                *(int*)(nextNode + 8) = 0; // new head->prev = nullptr
            }
        }
    } else {
        int* prevNode = (int*)*(int*)(node + 8); // node->prev
        if (node == EARSLinkedList::tail) {
            EARSLinkedList::tail = prevNode;
            *(int*)(prevNode + 4) = 0; // new tail->next = nullptr
        } else {
            *(int*)(prevNode + 4) = *(int*)(node + 4); // prev->next = node->next
            *(int*)(*(int*)(node + 4) + 8) = *(int*)(node + 8); // next->prev = node->prev
        }
    }

    // Release the node (call virtual destructor or deallocator)
    (**(void (__thiscall**)(int*, int))(*EARSLinkedList::vtablePtr + 4))(node, 0);

    EARSLinkedList::count -= 1;

    *outputNewHeadPtr = *headPtr;
}