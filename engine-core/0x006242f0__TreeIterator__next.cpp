// FUNC_NAME: TreeIterator::next
void TreeIterator::next() {
    // Check if the tree is empty
    if (this->count == 0) {
        assert_break(); // FUN_00b97aea - likely an assertion
    }

    TreeNode* node = this->currentNode;  // unaff_ESI[1]

    if (node->flag == 0) { // current node's left subtree not yet visited
        TreeNode* leftChild = node->left; // *node (first field)
        if (leftChild->flag == 0) { // left child's subtree not visited
            // Find the deepest node in the left subtree whose right child has a visited flag
            TreeNode* temp = leftChild->right; // +0x08
            while (temp->flag == 0) {
                leftChild = temp;
                temp = temp->right;
            }
            this->currentNode = leftChild;
            return;
        }
        // Left child's subtree already visited, climb up the tree
        node = node->parent; // piVar2[1]
        // Iterate until we find an unvisited node that is not the left child of its parent
        while (node->flag == 0 && this->currentNode == node->left) {
            this->currentNode = node;
            node = node->parent;
        }
        if (this->currentNode->flag != 0) {
            assert_break();
            return;
        }
        this->currentNode = node;
    } else { // current node already visited - move to right child
        TreeNode* rightChild = node->right; // piVar2[2]
        this->currentNode = rightChild;
        if (rightChild->flag != 0) {
            assert_break();
            return;
        }
    }
}