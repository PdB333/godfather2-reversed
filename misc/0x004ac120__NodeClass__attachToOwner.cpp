// FUNC_NAME: NodeClass::attachToOwner
NodeClass* __thiscall NodeClass::attachToOwner(Owner* owner) 
{
    // Call initialization function on owner (likely sets up internal state)
    initializeOwner(owner); // FUN_004ab950

    // Set vtable pointer to class-specific vtable
    this->vtable = &g_pfnNodeClassVtable; // PTR_LAB_00e356ac

    // Pointers to the intrusive linked-list node members at offsets +0x48 and +0x4C
    int** ppNext = &this->next;          // piVar1 = &this->next (+0x48)
    *ppNext = nullptr;                   // Initialize next to null
    this->prev = 0;                      // Clear previous pointer

    // Determine the address of the owner's next field (where we want to attach)
    int* pOwnerNextField;
    if (owner->pHeadNode == nullptr) {
        pOwnerNextField = 0;
    } else {
        // Owner has a node; its next field is at offset +0x48 from that node
        pOwnerNextField = reinterpret_cast<int*>(owner->pHeadNode + 0x48);
    }

    // If we are not already attached to the target list, detach from current and attach
    if (*ppNext != pOwnerNextField) {
        if (*ppNext != 0) {
            detachFromList(ppNext); // FUN_004daf90 - remove from current list
        }
        *ppNext = pOwnerNextField;  // Point our next to the owner's next field
        if (pOwnerNextField != 0) {
            // Insert ourselves into the doubly-linked list: 
            // Our prev = the previous node's prev (stored at pOwnerNextField+4)
            this->prev = *reinterpret_cast<int*>(pOwnerNextField + 4);
            // Update the previous node's prev to point to our next pointer
            *reinterpret_cast<int**>(pOwnerNextField + 4) = ppNext;
        }
    }

    return this;
}