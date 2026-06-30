// FUNC_NAME: NodeManager::destroyAllNodes
void __thiscall NodeManager::destroyAllNodes(Node* node) {
    // Traverse the linked list of nodes, processing children recursively
    // and calling a virtual destructor for each node.
    // The loop continues while the node's flag at offset 0x15 is zero (indicating it should be processed).
    while (node->flag == 0) {
        // Recursively destroy the child subtree (offset 0x08)
        destroyAllNodes(node->child);

        // Call the virtual function at vtable index 1 (offset 4 from vtable pointer)
        // This function likely destroys the node, taking a size parameter (0x18 = 24 bytes)
        // vtable pointer is stored at this+0x04
        (**(code **)(**(int **)((char*)this + 4) + 4))(node, 0x18);

        // Move to the next node in the list (offset 0x00)
        node = node->next;
    }
}