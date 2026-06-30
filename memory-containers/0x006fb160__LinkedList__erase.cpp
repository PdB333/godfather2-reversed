// FUNC_NAME: LinkedList::erase
// Function at 0x006fb160: Removes a node from a doubly linked list using an iterator pointer.
// Updates the iterator to point to the next node after removal.
// List structure: offset 0x00 = head, 0x04 = tail, 0x08 = count, 0x10 = vtable pointer (for node destruction)
// Node structure: offset 0x08 = next, 0x0c = prev

struct ListNode {
    int field_0;       // +0x00: unknown data
    int field_4;       // +0x04: unknown data
    ListNode* next;    // +0x08
    ListNode* prev;    // +0x0c
};

void __thiscall LinkedList::erase(void* this, int unusedParam, ListNode** iteratorPtr)
{
    ListNode* nodeToRemove = *iteratorPtr;
    ListNode* nextNode = (nodeToRemove != nullptr) ? nodeToRemove->next : nullptr;

    // Advance iterator to next node
    *iteratorPtr = nextNode;

    // Update list head/tail pointers
    if (nodeToRemove == this->head) {
        if (nodeToRemove == this->tail) {
            // Removing the only node
            this->head = nullptr;
            this->tail = nullptr;
        } else {
            // Removing head, update head to next
            this->head = nextNode;
            if (nextNode != nullptr) {
                nextNode->prev = nullptr;
            }
        }
    } else if (nodeToRemove == this->tail) {
        // Removing tail, update tail to previous
        ListNode* prevNode = nodeToRemove->prev;
        this->tail = prevNode;
        if (prevNode != nullptr) {
            prevNode->next = nullptr;
        }
    } else {
        // Removing from middle: link neighbours
        ListNode* prevNode = nodeToRemove->prev;
        ListNode* nextNode = nodeToRemove->next;
        prevNode->next = nextNode;
        if (nextNode != nullptr) {
            nextNode->prev = prevNode;
        }
    }

    // Destroy the removed node via virtual destructor (second vtable entry, offset 4)
    // vtable pointer is at this+0x10
    void* vtable = *(void**)((char*)this + 0x10);
    void (*destroyNode)(ListNode*, int) = (void (*)(ListNode*, int))((int*)vtable)[1]; // offset 4
    destroyNode(nodeToRemove, 0);

    // Decrement count
    this->count--;
}