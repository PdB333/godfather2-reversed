// FUNC_NAME: LinkedListManager::setHead
// Address: 0x0077f420
// Role: Sets the head of a linked list. Assumes list nodes are embedded in containers at offset 0x48 (node entry).
// If the head changes, the old head is removed via FUN_004daf90. For non-null new head, the node's 'prev' pointer 
// (offset +4 from node entry) is set to the list head field, and the old 'prev' value is saved to this+0x60.
void __thiscall LinkedListManager::setHead(LinkedContainer* container) {
    // Convert container pointer to the embedded list node entry (offset 0x48)
    void* newNodeEntry = (container == nullptr) ? nullptr : reinterpret_cast<char*>(container) + 0x48;

    // Pointer to the head pointer field (this + 0x5c)
    void** headPtr = reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0x5c);

    if (*headPtr != newNodeEntry) {
        // If there was an existing head, remove it from the list
        if (*headPtr != nullptr) {
            FUN_004daf90(headPtr);  // Removes the node pointed to by *headPtr
        }

        // Set new head
        *headPtr = newNodeEntry;

        if (newNodeEntry != nullptr) {
            // Save the old prev pointer of the new node to this+0x60 (possibly used for list tail or undo)
            *(reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0x60)) =
                *reinterpret_cast<void**>(reinterpret_cast<char*>(newNodeEntry) + 4);

            // Set the new node's prev pointer to point back to the list head field (circular/self-referential)
            *reinterpret_cast<void***>(reinterpret_cast<char*>(newNodeEntry) + 4) = headPtr;
        }
    }
}