// FUNC_NAME: TreeIterator::nextNode

void __fastcall TreeIterator::nextNode(int *this) {
    // +0x00: m_count (should be non-zero if tree is valid)
    // +0x04: m_current (pointer to current TreeNode)

    char flagCurrent;
    char flagChild;
    TreeNode *node;
    TreeNode *child;
    TreeNode *parent;

    if (this[0] == 0) {
        AssertFail(); // tree is empty or invalid
    }

    node = (TreeNode *)this[1]; // m_current

    if (node->flag == 0) { // node not visited yet
        TreeNode *leftChild = node->leftChild; // +0x00
        if (leftChild->flag == 0) {
            // descend into left child, then follow rightmost chain
            child = leftChild->rightChild; // +0x08
            flagChild = child->flag; // +0x15
            while (flagChild == 0) {
                child = child->rightChild; // +0x08
                flagChild = child->flag;
            }
            this[1] = (int)child;
            return;
        }
        // left child already visited, move to parent's right subtree or up
        node = (TreeNode *)node->parent; // +0x04
        flagCurrent = node->flag;
        while (flagCurrent == 0 && this[1] == (int)node->leftChild) {
            this[1] = (int)node;
            node = (TreeNode *)node->parent; // +0x04
            flagCurrent = node->flag;
        }
        if (this[1] != 0 && ((TreeNode *)this[1])->flag != 0) {
            AssertFail();
            return;
        }
        this[1] = (int)node;
    } else {
        // node already visited, move to right child
        TreeNode *rightChild = (TreeNode *)node->rightChild; // +0x08
        this[1] = (int)rightChild;
        if (rightChild != nullptr && rightChild->flag != 0) {
            AssertFail();
            return;
        }
    }
}