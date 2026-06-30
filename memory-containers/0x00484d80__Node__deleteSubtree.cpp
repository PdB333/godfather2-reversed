// FUNC_NAME: Node::deleteSubtree
// Reconstructed C++ for function at 0x00484d80
// Recursively deletes a node and its children, then moves to next sibling.
// Node structure:
// +0x00 -> Node* next (next sibling)
// +0x08 -> Node* child (first child)
// +0x15 -> char flag (0 = alive, non-zero = already deleted/skip)

void Node::deleteSubtree(Node* node) {
    // Continue while the node is flagged as alive (flag == 0)
    while (node->flag == 0) {
        // Recursively delete child subtree first (post-order)
        deleteSubtree(node->child);

        // Save next sibling before deleting current node
        Node* nextNode = node->next;

        // Delete/deallocate the current node (implementation in 0x009c8eb0)
        deleteNode(node); // FUN_009c8eb0

        // Move to the next sibling
        node = nextNode;
    }
    // If flag is non-zero, skip node (already processed or marked)
}