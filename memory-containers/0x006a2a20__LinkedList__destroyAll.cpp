// FUNC_NAME: LinkedList::destroyAll
// Function address: 0x006a2a20
// Role: Destructor for all nodes in a circular doubly linked list.
// Iterates over the list starting from the first node (head->next) and calls destroyNode on each,
// until it reaches back to the sentinel head (this).

struct ListNode {
    ListNode* next; // +0x00
    // other data follows
};

// Forward declaration of node destructor (at 0x009c8f10)
void destroyNode(ListNode* node);

void __thiscall LinkedList::destroyAll(void) {
    ListNode* currentNode = this->next;
    while (currentNode != this) {
        ListNode* nextNode = currentNode->next;
        destroyNode(currentNode);
        currentNode = nextNode;
    }
}