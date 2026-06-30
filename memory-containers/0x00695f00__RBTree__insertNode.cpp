// FUNC_NAME: RBTree::insertNode
void __thiscall RBTree::insertNode(int thisPtr, int *outIterator, bool insertAfter, RBTreeNode *hintNode, void *data)
{
    int size = *(int *)(thisPtr + 8);
    if (size > 0xaaaaaa8) {
        // Tree too long exception (map/set<T> too long)
        std::_Throw(std::exception("map/set<T> too long"));
    }

    // Allocate new node (0x28 bytes)
    RBTreeNode *newNode = (RBTreeNode *)operator new(0x28);
    if (newNode) {
        newNode->parent = (RBTreeNode *)thisPtr[1]; // header sentinel
        newNode->left = (RBTreeNode *)hintNode;
        newNode->right = (RBTreeNode *)thisPtr[1];
        // Copy key/data from data (assuming data has fields at +0x10, +0x14)
        newNode->key = *(int *)((char *)data + 0x10);
        newNode->value = *(int *)((char *)data + 0x14);
        newNode->color = 0; // red
        newNode->extraFlag = 0; // +0x25 byte
    }

    // Increment size
    (*(int *)(thisPtr + 8))++;

    // Insert into tree based on hint and direction
    RBTreeNode *head = *(RBTreeNode **)(thisPtr + 4);
    if (hintNode == head) {
        head->left = newNode;
        *(RBTreeNode **)(thisPtr + 4) = newNode;
        head->right = newNode;
    } else if (!insertAfter) {
        hintNode->right = newNode;
        if (hintNode == *(RBTreeNode **)(head + 8)) { // hint is rightmost
            *(RBTreeNode **)(head + 8) = newNode;
        }
    } else {
        hintNode->left = newNode;
        if (hintNode == *(RBTreeNode **)head) { // hint is leftmost
            *(RBTreeNode **)head = newNode;
        }
    }

    // Red-black fixup
    RBTreeNode *current = newNode;
    do {
        char color = current->color;
        if (color != 0) { // if black, done
            break;
        }
        RBTreeNode *parent = current->parent;
        RBTreeNode *grandparent = parent->parent;
        if (parent == grandparent->left) {
            RBTreeNode *uncle = grandparent->right;
            if (uncle->color != 0) { // uncle black
                parent->color = 1; // black
                uncle->color = 1;   // black
                grandparent->color = 0; // red
                current = grandparent;
                continue;
            }
            if (current == parent->right) {
                // rotate left
                current = parent;
                RBTree::rotateLeft(parent);
                parent = current->parent;
                grandparent = parent->parent;
            }
            parent->color = 1;
            grandparent->color = 0;
            RBTree::rotateRight(grandparent);
        } else {
            RBTreeNode *uncle = grandparent->left;
            if (uncle->color != 0) {
                parent->color = 1;
                uncle->color = 1;
                grandparent->color = 0;
                current = grandparent;
                continue;
            }
            if (current == parent->left) {
                current = parent;
                RBTree::rotateRight(parent);
                parent = current->parent;
                grandparent = parent->parent;
            }
            parent->color = 1;
            grandparent->color = 0;
            RBTree::rotateLeft(grandparent);
        }
    } while (true);

    // Root is always black
    RBTreeNode *root = *(RBTreeNode **)(thisPtr + 4);
    root->color = 1;

    // Set output iterator
    outIterator[0] = thisPtr;
    outIterator[1] = (int)newNode;
}