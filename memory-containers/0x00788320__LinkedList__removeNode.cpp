// FUNC_NAME: LinkedList::removeNode

struct ListNode {
    ListNode* prev; // +0x00? Actually offset 0 is not used here, but we have prev at +4, next at +8. So likely the struct has something else at +0? But for simplicity, we'll define as:
    int unknown0;   // +0x00
    ListNode* prev; // +0x04
    ListNode* next; // +0x08
};

struct LinkedList {
    int count;      // +0x28 (offset may vary, but from code it's at +0x28)
    // other members...
};

void __thiscall LinkedList::removeNode(LinkedList* this, ListNode* node) {
    // Decrement the count of nodes in the list
    this->count--;

    // Get the node's neighbors
    ListNode* nextNode = node->next; // +0x08
    ListNode* prevNode = node->prev; // +0x04

    // Update the next node's previous pointer to skip this node
    nextNode->prev = prevNode;

    // Update the previous node's next pointer to skip this node
    prevNode->next = nextNode;
}