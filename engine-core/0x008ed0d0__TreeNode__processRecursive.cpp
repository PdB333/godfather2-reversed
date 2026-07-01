// FUNC_NAME: TreeNode::processRecursive
struct TreeNode {
    TreeNode* next;             // +0x00 next sibling
    int field4;                 // +0x04
    TreeNode* child;            // +0x08 first child
    // ... other fields ...
    char inactiveFlag;          // +0x19 non-zero means node is inactive/sentinel
};

void processRecursive(TreeNode* node) {
    char flag = *(char*)((int)node + 0x19);
    while (flag == '\0') {
        // Recurse into children first (post-order)
        processRecursive(node->child);

        TreeNode* nextNode = node->next;
        FUN_008eb7a0();
        FUN_009c8eb0(node);

        node = nextNode;
        flag = *(char*)((int)nextNode + 0x19);
    }
    // Termination: encountering a node with non-zero flag stops traversal
}