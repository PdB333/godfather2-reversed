// FUNC_NAME: TreeIterator::increment
// Function address: 0x005e15c0
// Role: Advances an iterator to the next node in an inorder traversal of a binary search tree.
// Uses a flag at +0x15 (likely a color indicator, 0 = black, non-zero = red) to determine traversal direction.
// Calls FUN_00b97aea on invalid states (probably assertion failure).

class TreeIterator {
public:
    struct TreeNode {
        TreeNode* left;   // +0x00
        TreeNode* right;  // +0x04
        TreeNode* parent; // +0x08
        // +0x0C to +0x14: unknown/padding
        char color;       // +0x15 (0 = black, non-zero = red)
    };

    TreeNode* root_;    // +0x00 (pointer to tree root)
    TreeNode* current_; // +0x04 (current node in iteration)

    void increment(void) {
        // If the tree is empty, error.
        if (root_ == nullptr) {
            FUN_00b97aea(); // assertion/error
        }

        TreeNode* node = current_;

        // If current node is black (color == 0), we need to find the next node.
        if (node->color == 0) {
            TreeNode* parent = node->parent; // parent of current node

            // If parent is red (non-zero), we are in a right subtree and need to go up.
            if (parent->color != 0) {
                node = node->right; // move to right child (or start of upward traversal)
                // Walk up the tree while:
                // - node is black
                // - current_ (which is still the original node) equals the parent of the new node
                while (node->color == 0 && current_ == node->parent) {
                    current_ = node;
                    node = node->right;
                }
                current_ = node;
                return;
            }
            // Parent is black: traverse left subtree of the ancestor.
            else {
                // Move to the leftmost node of the cousin subtree.
                TreeNode* ancestor = parent->left; // first field of parent (left child)
                TreeNode* temp = ancestor; // save for traversal
                while (temp->color == 0) {
                    ancestor = temp;
                    temp = temp->left;
                }
                current_ = ancestor;
                return;
            }
        }
        // If current node is red, error.
        else {
            FUN_00b97aea(); // assertion/error
            return;
        }
    }
};