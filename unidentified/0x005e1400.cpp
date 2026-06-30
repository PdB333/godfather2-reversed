// FUNC_ADDR: 0x005e1400
// Role: Post-order depth-first traversal of a node tree, calling a virtual processor on each node.
// The traversal continues until it encounters a node with non-zero processedFlag (byte at +0x15).
// Recursively processes children first, then calls processor->processNode(node, 0x18), then moves to sibling.

// Node structure offsets:
// +0x00: TreeNode* pNextSibling
// +0x04: void* unknown (often some data or other link)
// +0x08: TreeNode* pChild
// +0x15: uint8_t processedFlag (0 = unprocessed, non-zero = skip)

class NodeProcessor {
public:
    virtual void processNode(void* node, int arg) = 0; // vtable index 1 (offset 4)
};

class EntityManager {
public:
    // offset +0x00: (some other member, e.g., int or pointer)
    NodeProcessor* processor; // +0x04

    // Recursive tree traversal
    void traverseNodeTree(TreeNode* node) {
        while (node->processedFlag == 0) {
            // Process child subtree first (depth-first)
            traverseNodeTree(node->pChild);
            // Call virtual processor on current node with constant 0x18 (possibly node size or operation flags)
            processor->processNode(node, 0x18);
            // Move to next sibling
            node = node->pNextSibling;
        }
    }
};