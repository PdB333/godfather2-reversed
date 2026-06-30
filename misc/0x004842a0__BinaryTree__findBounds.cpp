// FUNC_NAME: BinaryTree::findBounds
// Function at 0x004842a0: BST search returning predecessor and successor leaf nodes.
// The tree uses an internal node where left/right child pointers at offset 0 and 4,
// key at offset 0xC, and a flag at offset 0x15 (non-zero indicates leaf).
// The output array (passed in EAX) receives four pointers: [this tree, predecessor, this tree, successor].

struct TreeNode {
    TreeNode* left;        // +0x00
    TreeNode* right;       // +0x04
    int unknown3;          // +0x08 (likely parent or data)
    unsigned int key;      // +0x0C
    char pad[8];           // +0x10..+0x14
    char leafFlag;         // +0x15 (0 = internal, non-zero = leaf/sentinel)
};

class BinaryTree {
public:
    TreeNode* root;        // +0x04 (offset from this)
    // ... other members

    // Finds the leaf node that would contain 'key', and its predecessor/successor bounding leaves.
    // 'output' is a pointer to an array of 4 TreeNode* (passed in EAX on x86).
    // output[0] = this
    // output[1] = predecessor leaf (largest key < target)
    // output[2] = this
    // output[3] = successor leaf (smallest key > target)
    void __thiscall findBounds(unsigned int key, TreeNode** output) {
        TreeNode* currentNode = this->root;
        TreeNode* predLeaf = nullptr;  // tracks the leaf from the last "go right" decision
        TreeNode* succLeaf = nullptr;  // tracks the leaf from the last "go left" decision

        // First traversal: find the successor (leaf with key just above target)
        if (currentNode->right->leafFlag == 0) { // check if right child exists (internal)
            TreeNode* next = currentNode->right;
            do {
                if (key < next->key) {
                    succLeaf = next;          // potential successor: this node's left subtree
                    next = next->left;
                } else {
                    next = next->right;
                }
            } while (next->leafFlag == 0);
        }

        // Second traversal: find the predecessor (leaf with key just below target)
        currentNode = this->root;
        if (currentNode->right->leafFlag == 0) {
            TreeNode* next = currentNode->right;
            do {
                if (next->key < key) {
                    next = next->right;
                } else {
                    predLeaf = next;          // potential predecessor: this node's right subtree
                    next = next->left;
                }
            } while (next->leafFlag == 0);
        }

        // Fill output array (passed in EAX)
        output[0] = (TreeNode*)this;   // EAX[0] = this
        output[1] = predLeaf;          // EAX[1] = predecessor leaf
        output[2] = (TreeNode*)this;   // EAX[2] = this (duplicated)
        output[3] = succLeaf;          // EAX[3] = successor leaf
    }
};