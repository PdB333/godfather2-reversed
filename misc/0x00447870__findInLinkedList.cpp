// FUNC_NAME: findInLinkedList
struct ListNode {
    ListNode* next;        // +0x00
    // ... other fields (0x04-0x0C) ...
    int key;               // +0x10
};

ListNode* __thiscall findInLinkedList(void* thisPtr, int key) {
    ListNode* node = *(ListNode**)thisPtr;  // head pointer at this+0
    while (node != nullptr) {
        if (node->key == key) {
            return node;
        }
        node = node->next;
    }
    return nullptr;
}