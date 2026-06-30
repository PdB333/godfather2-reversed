// FUNC_NAME: ObjectIterator::advanceToNextActive

void ObjectIterator::advanceToNextActive() {
    char flag;
    TreeNode* currentNode;
    TreeNode* tempNode;
    TreeNode* nextNode;

    if (this->root == 0) {
        assertionFailure();
    }
    currentNode = this->current;  // +0x04

    if (*(char*)((int)currentNode + 0x15) == '\0') {  // current node is inactive
        tempNode = currentNode->parent;  // +0x00

        if (*(char*)((int)tempNode + 0x15) == '\0') {  // parent also inactive
            flag = *(char*)(*(int*)((int)tempNode + 8) + 0x15);  // check child of parent
            nextNode = *(TreeNode**)((int)tempNode + 8);  // +0x08 (right child?)

            while (flag == '\0') {
                flag = *(char*)(*(int*)((int)nextNode + 8) + 0x15);
                tempNode = nextNode;
                nextNode = *(TreeNode**)((int)nextNode + 8);
            }
            this->current = tempNode;  // set to the node just before first active descendant
            return;
        }

        // parent is active, move to next sibling
        currentNode = currentNode->next;  // +0x04 (left child?)
        flag = *(char*)((int)currentNode + 0x15);

        while (flag == '\0' && this->current == currentNode->parent) {
            this->current = currentNode;
            currentNode = currentNode->next;  // +0x04
            flag = *(char*)((int)currentNode + 0x15);
        }

        if (*(char*)(this->current + 0x15) != '\0') {
            assertionFailure();
            return;
        }
        this->current = currentNode;
    } else {
        // current node is active, move to child
        tempNode = currentNode->child;  // +0x08 (first child)
        this->current = tempNode;
        if (*(char*)((int)tempNode + 0x15) != '\0') {
            assertionFailure();
            return;
        }
    }
}