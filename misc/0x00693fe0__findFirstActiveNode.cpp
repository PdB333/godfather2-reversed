// FUNC_NAME: findFirstActiveNode
// Address: 0x00693fe0
// Role: Traverse a singly linked list where each node has a next pointer at offset 0
//       and an "active" flag byte at offset 0x25. Find the first node with a non‑zero flag.
//       The list is accessed through a handle (pointer to the head pointer).
void* findFirstActiveNode(void** listHandle) {
    // Dereference the handle to get the first node in the list.
    uint8_t* node = (uint8_t*)*listHandle;

    // Walk forward while the active byte (offset 0x25) is zero.
    while (*(int8_t*)(node + 0x25) == 0) {
        // Move to the next node (the pointer is stored at offset 0 of the current node).
        node = *(uint8_t**)node;
    }

    // Return the node pointer when a non‑zero flag is found.
    return (void*)node;
}