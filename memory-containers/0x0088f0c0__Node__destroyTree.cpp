// FUNC_NAME: Node::destroyTree
// Function address: 0x0088f0c0
// Role: Recursively destroys a tree-like structure where each node has a child and sibling pointer.
// Assumes node structure: [0x00] child pointer, [0x04] sibling pointer.
// Traverses depth-first (post-order): destroys child subtree, then frees current node, then processes sibling chain.

void Node::destroyTree(Node* node)
{
    if (node != nullptr) {
        do {
            // Recursively destroy child subtree (offset 0x00)
            destroyTree(node->child);
            
            // Save sibling pointer (offset 0x04) before freeing the node
            Node* nextSibling = node->sibling;
            
            // Free the current node (FUN_009c8f10 likely calls operator delete or destructor)
            freeNode(node);
            
            // Move to next sibling
            node = nextSibling;
        } while (nextSibling != nullptr);
    }
}