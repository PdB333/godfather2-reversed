// FUN_005e1230: TreeNodeIterator::moveToNext
void __thiscall TreeNodeIterator::moveToNext(void) {
    char flag;
    TreeNode* currentNode;
    TreeNode* nextNode;
    TreeNode* parent;
    TreeNode* root;

    // +0x00: root node pointer
    // +0x04: current node pointer (this is unaff_ESI[1])
    if (*(this + 0) == 0) {
        assertOrReset(); // FUN_00b97aea
    }

    currentNode = *(TreeNode**)(this + 4); // +0x04: m_current

    if (currentNode->flag_0x15 == 0) { // not visited yet
        nextNode = currentNode->leftChild; // +0x00
        if (nextNode->flag_0x15 == 0) {
            // Traverse down leftmost path from right subtree (inorder successor logic)
            TreeNode* temp = nextNode->rightChild; // +0x08
            flag = *(char*)(temp->rightChild + 0x15); // check temp's right child's flag
            while (flag == 0) {
                nextNode = temp;
                temp = temp->rightChild;
                flag = *(char*)(temp->rightChild + 0x15);
            }
            *(TreeNode**)(this + 4) = nextNode;
            return;
        } else {
            // Move up until we find a node that hasn't been visited or we become left child
            parent = currentNode->parent; // +0x04
            flag = parent->flag_0x15;
            while ((flag == 0) && (*(this + 4) == parent->leftChild)) {
                *(TreeNode**)(this + 4) = parent;
                parent = parent->parent;
                flag = parent->flag_0x15;
            }
            if (*(TreeNode**)(this + 4)->flag_0x15 != 0) {
                assertOrReset();
                return;
            }
            *(TreeNode**)(this + 4) = parent;
        }
    } else {
        // visited node: go to right child
        nextNode = currentNode->rightChild; // +0x08
        *(TreeNode**)(this + 4) = nextNode;
        if (nextNode->flag_0x15 != 0) {
            assertOrReset();
            return;
        }
    }
    return;
}