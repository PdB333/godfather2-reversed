// FUNC_NAME: avlRotateLeft
// Function address: 0x00574080
// This function performs a left rotation on an AVL tree node.
// nodePtr is a pointer to the pointer to the node to rotate (the old root of the subtree).
// treeRoot is a pointer to the overall tree root, updated if the rotated node becomes the new root.
// The node structure is assumed to have: height at +0x0, parent at +0x4, left child at +0x8, right child at +0xC.

struct AvlNode {
    int height;           // +0x0: height of the subtree (max child height + 1)
    AvlNode* parent;      // +0x4: pointer to parent node
    AvlNode* left;        // +0x8: left child
    AvlNode* right;       // +0xC: right child
};

void __fastcall avlRotateLeft(AvlNode** nodePtr, AvlNode** treeRoot)
{
    AvlNode* oldRoot = *nodePtr;              // iVar4: node to rotate
    AvlNode* newRoot = oldRoot->right;        // piVar1: right child (will become new root)
    AvlNode* oldParent = oldRoot->parent;     // iVar2: parent of old root

    // Perform rotation: oldRoot becomes left child of newRoot
    oldRoot->right = newRoot->left;           // oldRoot->right = newRoot->left
    if (newRoot->left != nullptr) {
        newRoot->left->parent = oldRoot;      // If newRoot had a left child, its parent becomes oldRoot
    }
    newRoot->left = oldRoot;                  // newRoot's left child is oldRoot
    oldRoot->parent = newRoot;                // oldRoot's parent is newRoot

    // Update heights of oldRoot and newRoot
    int leftHeight = (oldRoot->left != nullptr) ? oldRoot->left->height : -1;
    int rightHeight = (oldRoot->right != nullptr) ? oldRoot->right->height : -1;
    oldRoot->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;

    int newRootLeftHeight = (newRoot->left != nullptr) ? newRoot->left->height : -1;
    int newRootRightHeight = (newRoot->right != nullptr) ? newRoot->right->height : -1;
    newRoot->height = (newRootLeftHeight > newRootRightHeight ? newRootLeftHeight : newRootRightHeight) + 1;

    newRoot->parent = oldParent;              // newRoot's parent is the old parent

    // Update the parent's child pointer to point to the new root
    if (oldParent != nullptr) {
        if (oldParent->left == oldRoot) {
            oldParent->left = newRoot;
        } else {
            oldParent->right = newRoot;
        }
    } else {
        // If old root had no parent, it was the global root; update both pointers
        *treeRoot = newRoot;
    }

    *nodePtr = newRoot;                       // Always update the subtree root pointer
}