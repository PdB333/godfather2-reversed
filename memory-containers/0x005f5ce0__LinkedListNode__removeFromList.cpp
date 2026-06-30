// FUNC_NAME: LinkedListNode::removeFromList
// Address: 0x005f5ce0
// Removes this node from a doubly-linked list. Handles both normal and broken list cases.

struct LinkedListNode {
    LinkedListNode* next;   // +0x00
    LinkedListNode* prev;   // +0x04
    int inList;             // +0x08 (flag indicating membership)
};

void __thiscall LinkedListNode::removeFromList() {
    if (next != nullptr) {
        LinkedListNode* prevOfNext = next->prev; // Get the prev pointer of the next node
        if (prevOfNext == this) {
            // Normal case: next->prev correctly points back to this node
            next->prev = prev;  // Bypass this node from the next side
            next = nullptr;     // Detach this node from the list
            inList = 0;         // Clear flag
            return;
        }
        // Abnormal case: next->prev does not point to us (e.g. list is corrupted or circular)
        // Traverse forward to find the node that has 'this' as its next
        LinkedListNode* current = prevOfNext;
        while (current->next != this) {
            current = current->next;
        }
        current->next = prev;   // Bypass this node from the predecessor's side
        next = nullptr;         // Detach this node
    }
    inList = 0;  // Ensure flag is cleared even if next was null
}