// FUN_0046c640: SimObject::SimObject
void __thiscall SimObject::SimObject(SimObject* this)
{
    // Node structure for internal linked list (offset +0x4C)
    struct ListNode {
        void* data;   // +0x00
        ListNode* next; // +0x04
    };

    // Set vtable pointer (offset +0x00)
    this->m_vtable = reinterpret_cast<void**>(PTR_FUN_00e3280c);

    // Initialize vtable slot at +0x3C (0xF*4)
    this->m_messageHandler = reinterpret_cast<void**>(PTR_LAB_00e32828);

    // Set vtable slot at +0x48 (0x12*4) – first assignment
    this->m_processCallback = reinterpret_cast<void**>(PTR_LAB_00e32838);

    // Overwrite same slot with different value (likely derived class override)
    this->m_processCallback = reinterpret_cast<void**>(PTR_FUN_00e32808);

    // Clear the linked list at +0x4C (0x13*4)
    ListNode* currentNode = reinterpret_cast<ListNode*>(this->m_pendingListHead);
    while (currentNode != nullptr) {
        ListNode* nextNode = currentNode->next;
        currentNode->data = nullptr;
        currentNode->next = nullptr;
        currentNode = nextNode;
    }

    // Call base class initialization routines
    FUN_004083d0();
    FUN_0043b400();
}