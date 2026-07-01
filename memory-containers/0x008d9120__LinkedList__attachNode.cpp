// FUNC_NAME: LinkedList::attachNode
void __thiscall LinkedList::attachNode(int this, int node) {
    // Set flag at +0x25c to indicate modification
    *(uint *)(this + 0x25c) |= 1;

    // piVar1 points to the head pointer (pointer to pointer) at +0x22c
    int *headPtr = (int *)(this + 0x22c);

    // If node is non-null, advance to its 'next' field at offset 0x48
    if (node != 0) {
        node = node + 0x48;
    } else {
        node = 0;
    }

    // If the head pointer already points to this node's next field, do nothing
    if (*headPtr != node) {
        // If head was non-null, remove the old node from the list
        if (*headPtr != 0) {
            FUN_004daf90(headPtr); // likely removes the node pointed to by *headPtr
        }

        // Update head to point to the new node's next field
        *headPtr = node;

        if (node != 0) {
            // Save the old 'prev' pointer of the new node (at +0x4C) into this+0x230
            *(int *)(this + 0x230) = *(int *)(node + 4);
            // Set the new node's 'prev' pointer to point to the head pointer
            *(int **)(node + 4) = headPtr;
        }
    }
}