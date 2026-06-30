// FUNC_NAME: NodeContainer::releaseByIndex
// Address: 0x0045f250
// Role: Releases a node from a linked list by index. The container holds a pointer to a list head at +0x218.
// The list head has a first node pointer at +0x124. Each node has a next pointer at +0x124,
// an integer flag at +0x44, a validity byte at +0x121, and a vtable at offset 0.
// The virtual function at vtable[1] (release) is called with -1 to destroy the node.

void __thiscall NodeContainer::releaseByIndex(int index) {
    // Get the list head pointer from this container (offset +0x218)
    int *listHeadPtr = *(int **)(this + 0x218);
    if (listHeadPtr != 0) {
        // Get the first node from list head (offset +0x124)
        int *node = *(int **)(listHeadPtr + 0x124); // +0x124 / 4 = 0x49

        // Advance to the node at the given index
        for (int i = 0; i < index; i++) {
            if (node != 0) {
                // Move to next node via pointer at node offset +0x124
                node = (int *)node[0x49];
            }
        }

        if (node != 0) {
            // Clear flag at offset +0x44 (integer)
            node[0x44] = 0;
            // Clear validity byte at offset +0x121
            *(char *)(node + 0x121) = 0;
            // Call virtual destructor/release with -1 (immediate removal)
            (**(code **)(*node + 4))(node, 0xffffffff);
        }
    }
}