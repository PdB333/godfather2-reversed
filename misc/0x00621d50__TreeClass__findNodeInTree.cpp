// FUNC_NAME: TreeClass::findNodeInTree
void __thiscall TreeClass::findNodeInTree(uint *keyPtr, uint *outResult) {
    // this = unaff_ESI
    // outResult is a hidden pointer (in_EAX) to output buffer: [this, nodePtr]
    TreeNode *candidate;
    TreeNode *node;
    TreeNode *root;

    root = *(TreeNode **)((char *)this + 0x1c);   // tree root at this+0x1c
    node = root;
    // Traverse the tree: while node is a sentinel (byte at +0x15 == 0)
    while (*(char *)((char *)node + 0x15) == '\0') {
        if (node->key < *keyPtr) {
            // Go right
            node = (TreeNode *)node->right;        // offset 0x08
        } else {
            // Go left and update candidate
            node = (TreeNode *)node->left;         // offset 0x00
            candidate = node;
        }
    }
    // node is now a real leaf (non‑sentinel)
    root = *(TreeNode **)((char *)this + 0x1c);   // re‑read root
    if (candidate != root && candidate->key <= *keyPtr) {
        outResult[0] = (uint)this;
        outResult[1] = (uint)candidate;
        return;
    }
    outResult[0] = (uint)this;
    outResult[1] = (uint)root;
}