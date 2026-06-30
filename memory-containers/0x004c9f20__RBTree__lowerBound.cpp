// FUNC_NAME: RBTree::lowerBound
// 0x004c9f20 - Finds the first node with key >= given key, or the last node that is <= key. Returns via pointer in EAX (this, node).
// Structure: RBTree (this): +0x1c root (RBNode*)
// RBNode: +0x00 left, +0x04? (parent?), +0x08 right, +0x0C key (uint), +0x15 sentinel (bool)
void RBTree::lowerBound(uint key)
{
    RBNode* root = *(RBNode**)(this + 0x1c);
    RBNode* currentNode = root;
    RBNode* previousNode = root;

    // Traverse until hitting a sentinel node (empty leaf)
    if (*(char*)((int)currentNode->field_0x04 + 0x15) == '\0') // Check sentinel of parent? Typically root's right child?
    {
        currentNode = (RBNode*)currentNode->field_0x04;
        do
        {
            if (currentNode->key < key)
            {
                // Go right
                currentNode = (RBNode*)currentNode->right;
            }
            else
            {
                // Go left, remember this node as last satisfying condition
                currentNode = (RBNode*)currentNode->left;
                previousNode = currentNode;
            }
            currentNode = currentNode; // Unclear, but the loop condition uses the new currentNode
        } while (*(char*)((int)currentNode + 0x15) == '\0'); // Until sentinel
    }

    // Now currentNode is at a sentinel? Or the last node before sentinel.
    RBNode* resultNode;
    RBNode* rootCheck = *(RBNode**)(this + 0x1c);
    if (previousNode != rootCheck && previousNode->key <= key)
    {
        resultNode = previousNode;
    }
    else
    {
        resultNode = currentNode; // Should be root? Actually currentNode might be sentinel.
    }

    // Return via EAX pointer (assumed set by caller)
    *(int*)0 = (int)this;   // Simulated: write to EAX target
    *((int*)0 + 1) = (int)resultNode;
}