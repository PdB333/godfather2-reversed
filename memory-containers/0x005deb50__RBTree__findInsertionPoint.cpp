// FUNC_NAME: RBTree::findInsertionPoint
// Address: 0x005deb50
// Role: Searches the red-black tree for the appropriate insertion point for a given key.
// Returns a pair (parent, node) and a flag indicating if node needs to be inserted (1) or found (0).

// TreeNode structure (layout inferred):
struct TreeNode {
    TreeNode* left;      // +0x00
    TreeNode* parent;    // +0x04
    TreeNode* right;     // +0x08
    uint32_t key;        // +0x0C
    uint8_t isSentinel;  // +0x15 – non-zero for sentinel nodes
    // padding etc.
};

// RBTree class (partial)
class RBTree {
public:
    TreeNode* mHeader;  // +0x1C – points to a sentinel header node

    // Output pair structure: two pointers and a flag
    struct InsertionResult {
        TreeNode* parent;   // +0x00
        TreeNode* node;     // +0x04
        uint8_t insertFlag; // +0x08 – non-zero means insert, zero means found
    };

    InsertionResult* findInsertionPoint(InsertionResult* outResult, const uint32_t* keyPtr);
};

__thiscall InsertionResult* RBTree::findInsertionPoint(InsertionResult* outResult, const uint32_t* keyPtr) {
    // Get header node
    TreeNode* current = mHeader;

    // Assume we need to insert initially
    bool insertNeeded = true;

    // Check if the root node (current->parent) is not a sentinel (non-nil)
    TreeNode* root = current->parent; // parent of header is root
    if (root->isSentinel == 0) {      // real node present
        TreeNode* nextNode;
        // Traverse tree until we hit a sentinel
        do {
            current = root;
            // Compare target key with current node's key
            insertNeeded = (*keyPtr < current->key); // true if less
            if (insertNeeded) {
                nextNode = current->left;
            } else {
                nextNode = current->right;
            }
            root = nextNode;
        } while (root->isSentinel == 0);
    }

    // save original tree pointer (this)
    TreeNode* treeThis = reinterpret_cast<TreeNode*>(this);

    if (insertNeeded) {
        // Check if we are at the header's root position (empty tree)
        if (current == mHeader->parent) {
            // Create a new root node
            InsertionResult* newPair = FUN_005df5f0(this, &treeThis, 1, keyPtr);
            outResult->parent = newPair->parent; // typically the new node itself
            outResult->node = newPair->node;
            outResult->insertFlag = 1; // insert needed
            return outResult;
        }
        // Otherwise, it should be a valid insertion; call error handler if not
        FUN_005e1230(); // possibly assertion or error
    }

    // Re-check: if key < current->key, need to insert
    if (*keyPtr < current->key) {
        InsertionResult* newPair = FUN_005df5f0(this, &treeThis, /*insertNeeded*/1, keyPtr);
        outResult->parent = newPair->parent;
        outResult->node = newPair->node;
        outResult->insertFlag = 1;
        return outResult;
    }

    // Key already exists – return the node (current) and signal no insertion needed
    outResult->parent = treeThis; // the tree object (this)
    outResult->node = current;
    outResult->insertFlag = 0;
    return outResult;
}