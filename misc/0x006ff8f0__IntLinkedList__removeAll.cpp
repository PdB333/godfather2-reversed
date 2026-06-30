// FUNC_NAME: IntLinkedList::removeAll

struct ListNode {
    int value;      // +0x00
    ListNode* next; // +0x04
};

class IntLinkedList {
public:
    ListNode* head; // +0x00

    // Removes all nodes whose value equals the value pointed to by valuePtr.
    // Helper: removes a single node from the list and returns a pointer to the next pointer (or the new head pointer)
    void removeAll(const int* valuePtr);
};

// External helper function: removes the node at **nodePtr from the list whose head is at **headPtr.
// Returns a pointer to the new current node pointer (i.e., the next node after removal, or the new head if head removed).
extern ListNode** removeListNode(ListNode** headPtr, ListNode** nodePtr);

void __thiscall IntLinkedList::removeAll(const int* valuePtr) {
    ListNode* current = this->head;
    while (current != nullptr) {
        if (*valuePtr == current->value) {
            // Remove current node; helper returns pointer to the new "current" pointer location
            ListNode** newCurrentPtr = removeListNode(&(this->head), &current);
            // Update current to the node pointed to by the returned pointer (the next node after removal)
            current = *newCurrentPtr;
        } else {
            // Move to next node
            current = current->next;
        }
    }
}