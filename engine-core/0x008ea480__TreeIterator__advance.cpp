// FUNC_NAME: TreeIterator::advance
// Address: 0x008ea480
// Role: Advances a binary tree iterator to the next node in inorder traversal.
// The iterator structure has two fields: m_root (offset 0) and m_current (offset 4).
// Each tree node has: left child (offset 4), right child (offset 8), and a flag (offset 0x15)
// indicating whether the node has a right child (non-zero) or not (zero).
// The flag is used to determine traversal direction.

void __fastcall TreeIterator::advance(int* iterator)
{
    char flag;
    int* node;
    int* rightChild;
    int* leftChild;

    // If the iterator's root is null, call error handler
    if (iterator[0] == 0) {
        FUN_00b97aea(); // likely assertion or error
    }

    node = (int*)iterator[1]; // current node

    // The current node must have flag == 0 (no right child) for normal traversal
    if (*(char*)(node + 0x15) == '\0') {
        rightChild = (int*)node[2]; // node->right (offset +8)

        // If right child exists (flag non-zero), go to leftmost of right subtree
        if (*(char*)((int)rightChild + 0x15) != '\0') {
            // Start from left child of current node? Actually this branch seems to handle
            // the case where the current node has a right child. The code then goes to
            // the left child of the current node and walks left until a condition fails.
            // This is unusual; might be a different traversal order (preorder?).
            // For now, we follow the decompiled logic.
            leftChild = (int*)node[1]; // node->left (offset +4)
            flag = *(char*)((int)leftChild + 0x15);
            while (flag == '\0' && iterator[1] == leftChild[2]) {
                iterator[1] = (int)leftChild;
                leftChild = (int*)leftChild[1];
                flag = *(char*)((int)leftChild + 0x15);
            }
            iterator[1] = (int)leftChild;
            return;
        }
        // If right child has no right child (flag zero), go to parent via leftmost of right child?
        else {
            flag = *(char*)(*rightChild + 0x15); // flag of right child's left child
            leftChild = (int*)*rightChild; // left child of right child
            while (flag == '\0') {
                flag = *(char*)(*leftChild + 0x15);
                rightChild = leftChild;
                leftChild = (int*)*leftChild;
            }
            iterator[1] = (int)rightChild;
            return;
        }
    }
    // If current node's flag is non-zero, error
    FUN_00b97aea();
    return;
}