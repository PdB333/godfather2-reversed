// FUNC_NAME: traverseTreeNodeTree (generic tree traversal)
// Address: 0x00695700
// Reconstructed C++ for EA EARS engine tree node traversal
// The node structure contains a nextSibling pointer (+0x00), child pointer (+0x08),
// data pointer (+0x0C), function pointer (+0x18), and a flag byte at +0x29.

struct TreeNode {
    TreeNode* nextSibling;      // +0x00
    int unknown1;               // +0x04 (padding or other field)
    TreeNode* child;            // +0x08
    void* data;                 // +0x0C
    int unknown2;              // +0x10
    int unknown3;              // +0x14
    void (*callback)(void*);    // +0x18 function pointer, called with data if data != 0
    // byte at +0x29
    char stopFlag;              // +0x29 (non-zero means stop traversing this branch)
};

// Forward declaration of external function called on each node
void FUN_009c8eb0(TreeNode* node);

// Recursive traversal: visits child first, then processes current node, then next sibling.
void traverseTreeNode(TreeNode* node) {
    char flag = node->stopFlag;
    while (flag == '\0') {
        // Recurse into child subtree
        if (node->child != nullptr) {
            traverseTreeNode(node->child);
        }

        // Get next sibling pointer before processing current (might be modified?)
        TreeNode* nextNode = node->nextSibling;

        // If there is a data pointer, call the registered callback
        if (node->data != nullptr) {
            node->callback(node->data);
        }

        // Call the standard node processing function (likely cleanup or notify)
        FUN_009c8eb0(node);

        // Move to next sibling
        node = nextNode;
        flag = node->stopFlag;
    }
}