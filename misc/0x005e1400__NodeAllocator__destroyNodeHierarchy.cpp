// FUNC_NAME: NodeAllocator::destroyNodeHierarchy
// Function address: 0x005e1400
// Role: Recursively destroys a tree of nodes, deallocating each node via a virtual function.

void __thiscall NodeAllocator::destroyNodeHierarchy(Node* node) {
    // Check if node is already destroyed (flag at offset 0x15)
    // Node structure: +0x00 next sibling, +0x08 child, +0x15 destruction flag
    char flag = *(char*)((int)node + 0x15);
    while (flag == '\0') {
        // Recursively destroy child subtree
        destroyNodeHierarchy(*(Node**)((int)node + 8));  // node->child

        // Save next sibling before deallocating current node
        Node* nextNode = (Node*)*(int*)node;  // node->next

        // Deallocate node via virtual function (vtable+4, slot index 1)
        // The allocator's vtable pointer is stored at offset 4 of this object
        (**(code**)(**(int**)((int)this + 4) + 4))(node, 0x18);  // deallocate(node, size=24)

        // Move to next sibling
        node = nextNode;

        // Check flag for new node
        flag = *(char*)((int)node + 0x15);
    }
}