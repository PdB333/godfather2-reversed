// FUNC_NAME: NodeManager::recursiveFreeNodes

// Reconstructed from 0x004cae20
// This function recursively frees a tree of nodes. Each node has a sibling pointer at offset 0,
// a child pointer at offset 8, and a flag byte at offset 0x15 (0 = not yet freed).
// The manager object has a vtable at offset +0x04, whose entry [1] is a deallocation function
// that takes (Node* node, int size = 0x18).

struct Node {
    Node* next;        // +0x00: next sibling in the list
    int unknown;       // +0x04: unused? (preserved for alignment)
    Node* child;       // +0x08: first child node
    // padding to +0x15
    char freedFlag;    // +0x15: 0 if node is still active, non-zero if already freed
    // total size: 0x18 (24 bytes)
};

class NodeManager {
public:
    void recursiveFreeNodes(Node* node);
private:
    int field_0x00;                    // +0x00: unknown
    void** vtable;                     // +0x04: vtable pointer
};

void NodeManager::recursiveFreeNodes(Node* node) {
    // Continue while the current node's flag indicates it is still active (0 = not freed)
    while (node->freedFlag == 0) {
        // Recursively free the child subtree first (post-order)
        recursiveFreeNodes(node->child);

        // Save the next sibling before freeing the current node
        Node* nextNode = node->next;

        // Call the deallocation function from the vtable (entry index 1)
        // The node size is 0x18 (24 bytes)
        void (*deallocFunc)(Node*, int) = (void (*)(Node*, int))this->vtable[1];
        deallocFunc(node, 0x18);

        // Move to the next sibling
        node = nextNode;
        // The loop condition will re-check the freedFlag of the new node.
        // The tree is assumed to be terminated by a node with freedFlag != 0,
        // ending the loop naturally.
    }
}