// FUNC_NAME: LinkedList::replaceHead

struct ListNode {
    // +0x00: unknown (likely data or padding)
    ListNode* next;   // +0x04
    ListNode** pprev; // +0x08
};

class LinkedList {
public:
    ListNode* head; // +0x00

    // Replace the current head node with the node pointed to by *newNodePtr.
    // The old head is removed from the list (its pprev is cleared).
    // *newNodePtr is set to nullptr after the operation.
    void replaceHead(ListNode** newNodePtr) {
        if (head) {
            head->pprev = nullptr; // detach old head from the list
            head = nullptr;
        }
        head = *newNodePtr;
        if (head) {
            head->pprev = &head; // point back to the head pointer variable
            *newNodePtr = nullptr; // clear the source pointer
        }
    }
};