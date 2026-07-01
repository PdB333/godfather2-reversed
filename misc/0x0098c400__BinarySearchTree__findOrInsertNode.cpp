// FUNC_NAME: BinarySearchTree::findOrInsertNode
// Address: 0x0098c400
// This function performs a binary search tree lookup and optionally inserts a new node.
// It returns a pair: (node pointer, flag) where flag=0 means found, flag=1 means inserted.

struct TreeNode {
    TreeNode* left;      // +0x00
    TreeNode* right;     // +0x04
    // possibly parent at +0x08, other fields
    uint key;            // +0x10
};

// Forward declarations of helper functions
TreeNode* getPredecessor(TreeNode* node); // FUN_00ab3c90
void insertNode(TreeNode** root, TreeNode* parent, uint* key, int param); // FUN_0098c0f0

class BinarySearchTree {
public:
    // +0x04: unknown pointer (maybe sentinel)
    // +0x08: unknown pointer (maybe min node)
    // +0x0C: root node pointer

    // Returns a pair: (node, foundFlag) where foundFlag=0 if key exists, 1 if inserted
    void* __thiscall findOrInsertNode(void* outputPair, uint* key) {
        TreeNode* current;
        TreeNode* parent;
        bool goLeft;

        parent = reinterpret_cast<TreeNode*>(this + 4); // start with sentinel? Actually this+4 is used as initial parent
        goLeft = true;

        if (*(TreeNode**)(this + 0x0C) != nullptr) {
            current = *(TreeNode**)(this + 0x0C); // root
            do {
                parent = current;
                goLeft = *key < current->key;
                if (goLeft) {
                    current = current->right; // +0x04
                } else {
                    current = current->left;  // +0x00
                }
            } while (current != nullptr);
        }

        TreeNode* result = parent;
        if (goLeft) {
            if (parent == *(TreeNode**)(this + 0x08)) {
                goto insert;
            }
            result = getPredecessor(parent);
        }

        if (*key <= result->key) {
            // Key already exists
            *reinterpret_cast<TreeNode**>(outputPair) = result;
            *reinterpret_cast<char*>(outputPair + 4) = 0; // flag = 0 (found)
            return outputPair;
        }

insert:
        // Insert new node
        insertNode(reinterpret_cast<TreeNode**>(&key), parent, key, 0);
        *reinterpret_cast<TreeNode**>(outputPair) = reinterpret_cast<TreeNode*>(key); // key pointer becomes new node? Actually param_3 is passed as new node pointer
        *reinterpret_cast<char*>(outputPair + 4) = 1; // flag = 1 (inserted)
        return outputPair;
    }
};