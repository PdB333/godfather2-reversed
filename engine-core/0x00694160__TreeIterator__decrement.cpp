// FUNC_NAME: TreeIterator::decrement
// Address: 0x00694160
// This function implements the decrement operator (operator--) for a binary search tree iterator.
// The tree uses a sentinel node (flag at +0x29 non-zero) and has left, parent, right pointers.

struct TreeNode {
    TreeNode* left;   // +0x00
    TreeNode* parent; // +0x04
    TreeNode* right;  // +0x08
    // data follows
    char flag;        // +0x29 (0 = real node, non-zero = sentinel/nil)
};

struct TreeIterator {
    TreeNode* treeHeader; // +0x00 (pointer to the tree's header node)
    TreeNode* currentNode; // +0x04
};

void __fastcall TreeIterator::decrement(TreeIterator* this)
{
    // Assert the tree pointer is valid
    if (this->treeHeader == 0) {
        assertion_failed();
    }

    TreeNode* currentNode = this->currentNode;

    // If current node is not the sentinel
    if (currentNode->flag == 0) {
        TreeNode* leftChild = currentNode->left;

        // If left child is not the sentinel, find the rightmost node in the left subtree
        if (leftChild->flag == 0) {
            TreeNode* rightChild = leftChild->right;    // +0x08
            while (rightChild->flag == 0) {
                leftChild = rightChild;
                rightChild = rightChild->right;         // +0x08
            }
            this->currentNode = leftChild;
            return;
        }
        // Else, go up until we come from a right child link
        else {
            TreeNode* parent = currentNode->parent;     // +0x04
            while ((parent->flag == 0) && (this->currentNode == parent->left)) {
                this->currentNode = parent;
                parent = parent->parent;                // +0x04
            }
            if (this->currentNode->flag != 0) {
                assertion_failed();
                return;
            }
            this->currentNode = parent;
        }
    }
    else {
        // Current node is the sentinel: move to its right child (which is the rightmost real node)
        TreeNode* rightMost = currentNode->right;       // +0x08
        this->currentNode = rightMost;
        if (this->currentNode->flag != 0) {
            assertion_failed();
            return;
        }
    }
}