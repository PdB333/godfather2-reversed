// FUNC_NAME: findActiveNode
// Address: 0x008ea0e0
// Traverses a singly-linked list of nodes (with next ptr at +0x00 and active flag at +0x15) until a node with non-zero active flag is found. Returns that node.

struct ListNode {
    ListNode* next;   // +0x00
    // ... other fields ...
    uint8_t active;   // +0x15 (0 = inactive, non-zero = active)
};

ListNode* findActiveNode(ListNode** headPtr) {
    ListNode* node = *headPtr;
    while (node->active == 0) {
        node = node->next;
    }
    return node;
}