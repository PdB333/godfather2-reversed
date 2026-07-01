// FUNC_NAME: SimManager::updateActiveObjects
void __fastcall SimManager::updateActiveObjects(SimManager* this) {
    // Get the list structure from this+0x0C
    // +0x0C: pointer to a container; dereference +4 gives the linked-list head pointer
    int* listContainer = *(int**)((int)this + 0xC);
    int* listPtr = (int*)(listContainer[1]); // +0x04 in the container

    // The list uses a sentinel node at listPtr+0x18
    ListNode* sentinel = *(ListNode**)(listPtr + 0x18); // +0x18: sentinel address
    ListNode* node = sentinel->next; // +0x00: next pointer in node

    // Iterate through the circular linked list until we hit the sentinel again
    while (node != sentinel) {
        // Check flag at offset 0x1B: bit 2 indicates "active/dirty" status
        if (node->flags & 0x02) {
            // Offset 0x10 holds a pointer to an associated object
            uint32_t objectPtr = node->objectPointer; // +0x10
            // Skip if null or special sentinel value 0x48 (likely a type/state tag)
            if (objectPtr != 0 && objectPtr != 0x48) {
                // Subtract 0x48 to get the actual base object pointer
                int* obj = (int*)(objectPtr - 0x48);
                // Check a flag at offset 0x18E: bit 0 cleared means "needs processing"
                if ((~*(uint8_t*)(obj + 0x18E) & 1) != 0) {
                    // Clear bit 3 at offset 0x18C (flag for "already processed" or similar)
                    *(uint32_t*)(obj + 0x18C) &= ~0x08;
                    // Call a handling function with a temp buffer, list context, and node
                    char tempBuffer[8];
                    FUN_0081c910(tempBuffer, listPtr, node);
                }
            }
        }
        node = node->next; // advance to next node in list
    }
}