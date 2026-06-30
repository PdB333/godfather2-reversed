// FUNC_NAME: BinaryTree::findNodeWithFlag
// Address: 0x006948e0
// This function traverses a binary tree starting from a root node (stored at this+4->[1]).
// It uses a comparison function (FUN_004d4b20) to decide direction: if result < 0, go right (offset 0x08);
// otherwise go left (offset 0x00). It stops when a node with a non-zero flag at offset 0x25 is encountered.
// Returns the parent node of the flagged node (the node before the flagged one in traversal).

struct TreeNode {
    TreeNode* left;   // +0x00
    TreeNode* right;  // +0x04  (unused in traversal, but part of node)
    TreeNode* parent; // +0x08  (used as right child? Actually offset 0x08 is used as "next" when comparison <0)
    // ... other fields
    char flag;        // +0x25  (non-zero indicates a special node)
};

struct TreeContainer {
    int field0;       // +0x00 (unused)
    TreeNode* root;   // +0x04 (pointer to root node)
};

TreeNode* __thiscall BinaryTree::findNodeWithFlag(int thisPtr, int param2) {
    TreeContainer* container = *(TreeContainer**)(thisPtr + 4);
    TreeNode* currentNode = container->root;  // root node
    char flag = *(char*)((int)currentNode + 0x25);
    TreeNode* previousNode = nullptr;

    while (flag == '\0') {
        int comparisonResult = FUN_004d4b20(param2);  // comparison function
        TreeNode* nextNode;
        if (comparisonResult < 0) {
            // Go right (offset 0x08)
            nextNode = (TreeNode*)(*(int*)((int)currentNode + 8));
        } else {
            // Go left (offset 0x00)
            nextNode = currentNode->left;
        }
        previousNode = currentNode;
        currentNode = nextNode;
        flag = *(char*)((int)nextNode + 0x25);
    }
    return previousNode;  // returns the node that was the parent of the flagged node
}