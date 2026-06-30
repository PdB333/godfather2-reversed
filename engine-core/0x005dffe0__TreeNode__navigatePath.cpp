// FUNC_NAME: TreeNode::navigatePath
void TreeNode::navigatePath(TreeNode* outPath[2], TreeNode* startNode, TreeNode* targetNode, TreeNode* startParent, TreeNode* targetParent) {
    int rootValue = **(int**)((int)this + 0x1c); // +0x1c: pointer to root node's pointer, then deref

    // Special case: start/target are at root level
    if ((startNode == 0 || startNode == this) && (targetNode == (TreeNode*)rootValue)) {
        if ((startParent == 0 || startParent == this) && (targetParent == (TreeNode*)rootValue)) {
            // Reset the linked list at root
            FUN_005e1350(*(undefined4*)(*(int*)((int)this + 0x1c) + 4)); // detach next
            *(int*)(*(int*)((int)this + 0x1c) + 4) = *(int*)((int)this + 0x1c); // next = self
            *(undefined4*)((int)this + 0x20) = 0; // +0x20: probably count or state
            *(undefined4*)*(undefined4*)((int)this + 0x1c) = *(undefined4*)((int)this + 0x1c); // prev = self
            *(int*)(*(int*)((int)this + 0x1c) + 8) = *(int*)((int)this + 0x1c); // something at +8 = self
            outPath[1] = (TreeNode*)**(int**)((int)this + 0x1c);
            outPath[0] = this;
            return;
        }
    }

    // General case: traverse from startNode to targetNode via tree
    while (true) {
        if ((startNode == 0 || startNode == startParent)) {
            FUN_005e09e0(); // assertion failed
        }
        if (startNode == targetNode) break;
        FUN_005e09e0(); // advance step
        FUN_005dec30(this, pathBuffer, startNode, targetNode); // record step
    }
    outPath[1] = targetNode;
    outPath[0] = startNode;
    return;
}