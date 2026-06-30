// FUNC_NAME: SlotContainer::~SlotContainer

void __fastcall SlotContainer::~SlotContainer(SlotContainer* this) {
    // Offset 0x04: m_object1 (pointer to another object)
    // Offset 0x08: m_object2
    // Offset 0x0C: m_object3
    // Offset 0x10: m_object4
    // Offset 0x14: m_linkedObject (freed conditionally)
    // Offset 0x28: m_listHead (linked list of nodes, each node has next pointer at offset 0)
    // Offset 0x0F (byte): m_ownsFlag (non-zero indicates that m_linkedObject and the list are owned)

    // Release four owned sub-objects
    callVirtualDestructor(this->m_object1, 0);
    callVirtualDestructor(this->m_object2, 0);
    callVirtualDestructor(this->m_object3, 0);
    callVirtualDestructor(this->m_object4, 0);

    // If we own the dynamically allocated list and the linked object
    if (*(char*)(this + 0x0F) != '\0') {
        // Free all nodes in the linked list
        LinkedListNode* currentNode = this->m_listHead; // param_1[10]
        while (currentNode != nullptr) {
            LinkedListNode* nextNode = currentNode->next; // *currentNode (first field is next ptr)
            callVirtualDestructor(currentNode, 0);
            currentNode = nextNode;
        }
        // Finally, free the linked object itself
        callVirtualDestructor(this->m_linkedObject, 0); // param_1[5]
    }
}