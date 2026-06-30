// FUNC_NAME: TreeNode::processNodes
// Address: 0x006956b0
// Role: Depth-first traversal of a tree-like structure. Processes nodes while their 'alive' flag at +0x25 is zero.
// Each node contains:
//   +0x00 : nextSibling (pointer to next sibling node)
//   +0x08 : child (pointer to first child node)
//   +0x0C : data (void* - argument passed to callback)
//   +0x18 : callback (void(*)(void*))
//   +0x25 : alive (byte, 0 = needs processing, non-zero = skip)

struct TreeNode {
    TreeNode* nextSibling;   // +0x00
    // +0x04 padding
    TreeNode* child;         // +0x08
    void* data;              // +0x0C
    // +0x10 - +0x17 unknown
    void (*callback)(void*); // +0x18
    // +0x1C - +0x24 unknown
    char alive;              // +0x25
};

// External function: likely frees/releases node resources (e.g., operator delete)
extern void FUN_009c8eb0(TreeNode* node);

void FUN_006956b0(TreeNode* node) {
    char alive = node->alive;

    while (alive == 0) {
        // Process children first (recursive)
        FUN_006956b0(node->child);

        TreeNode* nextSibling = node->nextSibling;

        // Call the node's callback on its data, if data is non-null
        if (node->data != 0) {
            node->callback(node->data);
        }

        // Cleanup/deallocate the current node
        FUN_009c8eb0(node);

        // Move to the next sibling
        node = nextSibling;
        alive = node->alive;
    }
}