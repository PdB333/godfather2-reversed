// FUNC_NAME: EntityManager::setCurrentNode

struct ListNode {
    int unknown;            // +0x00
    ListNode* next;         // +0x04 (next pointer in the intrusive list)
};

// External list removal function (FUN_004daf90)
extern void removeListNode(ListNode** headPtr);

void __thiscall EntityManager::setCurrentNode(void* this, void* container) {
    // EntityManager layout:
    //   vtable at +0x00
    //   ...
    //   ListNode* m_headNode at +0x74C (0x1d3 * 4)
    //   ListNode* m_savedNext at +0x750 (0x1d4 * 4)

    // Pointer to the head pointer field
    ListNode** headPtr = (ListNode**)((char*)this + 0x74C);
    ListNode* current = *headPtr;

    // Compute the container that owns the current node (node is at container+0x48)
    void* currentContainer = (current == nullptr) ? nullptr : (void*)((char*)current - 0x48);

    // If the requested container is already the current one, just notify
    if (container == currentContainer) {
        // vtable offset 0x25c → onActivate
        ((void (__thiscall*)(void*))(*(int*)(*(int*)this + 0x25c)))(this);
        return;
    }

    // Notify that the current node is about to change (vtable offset 0x260 → onDeactivate)
    ((void (__thiscall*)(void*))(*(int*)(*(int*)this + 0x260)))(this);

    // Convert the new container to its embedded node (at offset +0x48)
    ListNode* newNode = (container == nullptr) ? nullptr : (ListNode*)((char*)container + 0x48);

    if (*headPtr != newNode) {
        // Remove the old head node from the list if it exists
        if (*headPtr != nullptr) {
            removeListNode(headPtr);
        }

        // Set the new head
        *headPtr = newNode;

        if (newNode != nullptr) {
            // Save the new node's original next pointer into the manager's savedNext field
            *(ListNode**)((char*)this + 0x750) = newNode->next; // newNode->next is at +4

            // Link the new node's next pointer to point back to the head pointer variable
            // This creates an intrusive list where each node's next points to the address
            // of the pointer that points to the node (or the previous node’s next pointer).
            newNode->next = (ListNode*)headPtr;
        }
    }

    // Final notification (vtable offset 0x25c → onActivate)
    ((void (__thiscall*)(void*))(*(int*)(*(int*)this + 0x25c)))(this);
}