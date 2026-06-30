// FUNC_NAME: TreeNodeManager::recursiveDestroyNode

void __thiscall TreeNodeManager::recursiveDestroyNode(int *node) {
    int currentChild;
    int nextSibling;

    if (node != (int *)0x0) {
        // Iterate through the linked list of children starting at node[8] (+0x20)
        currentChild = node[8]; // node->firstChild
        while (currentChild != 0) {
            nextSibling = *(int *)(currentChild + 0x28); // child->nextSibling (offset +0x28)
            recursiveDestroyNode(currentChild); // Recursively destroy child
            currentChild = nextSibling;
        }

        // Remove this node from its parent's child list
        if (node == *(int **)(this + 4)) {
            // This node is the first child of the parent (this->firstChild)
            *(int *)(this + 4) = 0; // Clear the parent's first child pointer
        } else if (node[7] != 0) { // +0x1C: parent pointer
            // Call parent's vtable function at offset 0x1c to remove this node from sibling list
            (**(code **)(*(int *)node[7] + 0x1c))(node);
        }

        // Check if the node has a "keepAlive" flag (bit 0 at +0x14)
        if ((*(byte *)(node + 5) & 1) != 0) { // flags byte at offset 0x14
            node[5] = node[5] | 2; // Set bit 1 to mark as "pending delete" and return
            return;
        }

        // Otherwise, call the node's own destructor (vtable entry at +0x04) with argument 1
        (**(code **)(*node + 4))(1);
    }
    return;
}