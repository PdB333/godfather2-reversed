// FUNC_NAME: ObjectManager::destroyObject
// Struct representing an intrusive singly-linked list node embedded at offset +0x1C in containing objects
struct ListNode {
    // +0x00: (unknown, may be unused or prev pointer)
    // +0x04: next pointer
    void* next;
};

// External functions: list removal and memory deallocation
extern void slistRemove(void** listHeadPtr);
extern void deallocateObject(void** objectHandle);

void destroyObject(void* object) {
    // object is a pointer to the containing object with an embedded ListNode at offset 0x1C
    ListNode* node = nullptr;
    if (object != nullptr) {
        node = reinterpret_cast<ListNode*>(
            reinterpret_cast<uint8_t*>(object) + 0x1C
        );
    }

    // Temp: store old next pointer (unused, likely for debugging)
    // ListNode* oldNext = (node != nullptr) ? node->next : nullptr;

    if (node != nullptr) {
        // Set the node's next pointer to point to the stack variable itself,
        // creating a temporary, circular list head for the unlink operation
        node->next = &node;
    }

    // Unlink the node from whatever list it belongs to.
    // The function receives the address of the local pointer so it can modify it.
    slistRemove(reinterpret_cast<void**>(&node));

    // If the node pointer is still non-null, free the «object» memory.
    if (node != nullptr) {
        deallocateObject(reinterpret_cast<void**>(&node));
    }
}