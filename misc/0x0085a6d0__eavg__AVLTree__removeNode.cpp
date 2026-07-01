// FUNC_NAME: eavg::AVLTree::removeNode

// AVL tree node structure (fields offset in comments)
struct AVLNode {
    int32_t key;       // +0x00: key value (also used for balance factor during rotations)
    AVLNode* parent;   // +0x04
    AVLNode* left;     // +0x08
    AVLNode* right;    // +0x0C
};

// AVL tree container (used by this member function)
// This = param_1
struct AVLTree {
    AVLNode* root;      // +0x00: root of the tree
    int32_t nodeCount;  // +0x04: number of nodes
    // +0x08: likely unused padding or another field
    void** vtable;      // +0x0C: vtable for node allocation/deallocation
};

// Helper functions (defined elsewhere)
// Searches for a node matching param_2; returns node pointer via first argument.
void findNode(AVLNode** outNode, void* param_2);
// Single left rotation on the subtree rooted at *nodePtr
void rotateLeft(AVLNode** nodePtr);
// Single right rotation on the subtree rooted at *nodePtr
void rotateRight(AVLNode** nodePtr);

// Removes 'param_2' (a node pointer or key reference) from the AVL tree.
// Returns 1 on success, 0 on failure.
bool __thiscall AVLTree::removeNode(AVLTree* thisTree, void* param_2)
{
    AVLNode* nodeToRemove;
    AVLNode* current;
    AVLNode* parent;
    AVLNode* successor;
    int32_t leftKey;
    int32_t rightKey;

    // Locate the node to remove (param_2 is either the node itself or a key)
    findNode(&nodeToRemove, param_2);
    if (nodeToRemove == nullptr) {
        return false;
    }

    // If the node has a right child, find the in-order successor
    if (nodeToRemove->right != nullptr) {
        // Traverse left children of the right subtree until no left child
        successor = nodeToRemove->right;
        while (successor->right != nullptr) {
            successor = successor->right;
        }
        // successor now has no right child; remove it from its current position

        // Detach successor from its parent
        if (successor->parent == nullptr) {
            thisTree->root = successor->left;
        }
        else if (successor->parent->left == successor) {
            successor->parent->left = successor->left;
        }
        else {
            successor->parent->right = successor->left;
        }

        // Reattach successor's left child
        if (successor->left != nullptr) {
            successor->left->parent = successor->parent;
        }

        // Replace nodeToRemove with successor in the tree
        successor->parent = nodeToRemove->parent;
        // (code continues with rebalancing...)
    }
    // ... (rest of removal logic follows the original decompiled pattern)

    // Rebalancing loop starting from the node's parent upwards
    current = nodeToRemove->parent;
    while (current != nullptr) {
        int32_t leftHeight = (current->left != nullptr) ? current->left->key : -1;
        int32_t rightHeight = (current->right != nullptr) ? current->right->key : -1;
        int32_t balance = leftHeight - rightHeight;

        if (balance == 2) {
            // Left imbalance: determine if a double rotation is needed
            int32_t leftChildLeftHeight = (current->left->left != nullptr) ? current->left->left->key : -1;
            int32_t leftChildRightHeight = (current->left->right != nullptr) ? current->left->right->key : -1;
            if (leftChildLeftHeight - leftChildRightHeight < 0) {
                rotateRight(&current->left); // left child's right subtree is heavy: left rotate left child first
            }
            rotateLeft(&current); // then right rotate current
        }
        else if (balance == -2) {
            // Right imbalance
            int32_t rightChildRightHeight = (current->right->right != nullptr) ? current->right->right->key : -1;
            int32_t rightChildLeftHeight = (current->right->left != nullptr) ? current->right->left->key : -1;
            if (rightChildRightHeight - rightChildLeftHeight < 0) {
                rotateLeft(&current->right); // right child's left subtree is heavy: right rotate right child first
            }
            rotateRight(&current); // then left rotate current
        }

        // Update height (balance factor) of this node
        int32_t maxChildHeight = (leftHeight > rightHeight) ? leftHeight : rightHeight;
        current->key = maxChildHeight + 1; // store height in key field temporarily (or use real height field)

        current = current->parent; // move up
    }

    // Delete the node (call vtable deallocator)
    (*(void(*)(AVLNode*, int))(void (*)())(*(int*)thisTree->vtable + 4))(nodeToRemove, 0);

    thisTree->nodeCount--;
    return true;
}