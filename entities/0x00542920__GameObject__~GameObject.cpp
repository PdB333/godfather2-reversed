// FUNC_NAME: GameObject::~GameObject

void __fastcall GameObject::~GameObject(GameObject* this) {
    // Reset vtable pointer to base class (size ~0x5c entries)
    this->vtable = &g_BaseVtable;
    this->vtableEntries[0x0f] = &g_BaseVtable1;  // +0x3C
    this->vtableEntries[0x12] = &g_BaseVtable2;  // +0x48
    this->vtableEntries[0x14] = &g_BaseVtable3;  // +0x50
    this->vtableEntries[0x15] = &g_BaseVtable4;  // +0x54
    this->vtableEntries[0x16] = &g_BaseVtable5;  // +0x58

    // Free sub-object at offset +0x2B8 (e.g. a string or dynamically allocated struct)
    if (this->m_pSubObject != nullptr) {
        // Custom deallocate with size=8, tag from -4 offset
        deallocateTypedMemory(this->m_pSubObject, 8, *(this->m_pSubObject - 1), &someLabel);
        // Destruct the sub-object at address (m_pSubObject - 4)
        destructAtOffsetMinus4(this->m_pSubObject - 4);
    }

    // Handle first embedded intrusive list node at offset +0x2D0
    ListNode* listNode1 = &this->m_listNode1; // offset +0x2D0 (next), +0x2D4 (prev)
    this->m_listNode1.extra = 0; // +0x2D8

    // If the list is not empty and not a sentinel value 0x48 (magic)
    if (listNode1->next != nullptr && listNode1->next != (ListNode*)0x48) {
        // Perform cleanup on the object that owns the next node (offset -0x48)
        if (listNode1->next != nullptr) {
            GameObject* owner = (GameObject*)((uint8_t*)listNode1->next - 0x48);
            owner->someVirtualFunc(0);  // vtable+0x1C
        }
        if (listNode1->next != nullptr) {
            GameObject* owner = (GameObject*)((uint8_t*)listNode1->next - 0x48);
            owner->anotherVirtualFunc(); // vtable+0x3C offset 8
        }
        // Debug global check
        if (g_debugFlag != nullptr && checkDebugFlag(g_debugFlag) == false) {
            g_debugCounter++;
            setDebugFlag(g_debugFlag, 0x8000);
        }
    }

    // Remove this node from the first linked list
    if (listNode1->next != nullptr) {
        ListNode* nextNode = listNode1->next;
        if (nextNode->prev == listNode1) {
            // nextNode's prev points directly to this node: update to this node's prev
            nextNode->prev = listNode1->prev;
        } else {
            // Walk backwards through the list to find the node that points to this
            ListNode* walker = nextNode->prev;
            while (walker->prev != listNode1) {
                walker = walker->prev;
            }
            walker->prev = listNode1->prev;
        }
    }

    // Handle second embedded intrusive list node at offset +0x2B0
    ListNode* listNode2 = &this->m_listNode2; // offset +0x2B0 (next), +0x2B4 (prev)
    if (listNode2->next != nullptr) {
        ListNode* nextNode = listNode2->next;
        if (nextNode->prev == listNode2) {
            // Direct removal: set nextNode's prev to this node's prev
            nextNode->prev = listNode2->prev;
            // Final deallocation (custom operator delete or free)
            deallocateObject(this); // FUN_0045db70
            return;
        }
        // Else walk forward using next pointers to find the node that points to this
        ListNode* walker = nextNode->prev;
        while (walker->next != listNode2) {
            walker = walker->next;
        }
        walker->next = listNode2->prev;
    }

    // Final deallocation
    deallocateObject(this);
}