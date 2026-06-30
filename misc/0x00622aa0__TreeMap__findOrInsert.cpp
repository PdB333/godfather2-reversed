// FUNC_NAME: TreeMap::findOrInsert
// Function address: 0x00622aa0
// This function searches for a key in a red-black tree (or similar balanced BST).
// If found, it returns the node with flag=0; if not found, it inserts a new node and returns flag=1.
// Output structure: {TreeNode* parentNode, TreeNode* newNodeOrFound, char inserted}
// The tree nodes have sentinel nodes (flag at offset +0x25) to indicate leaves.

struct TreeNode {
    TreeNode* left;       // +0x00
    TreeNode* right;      // +0x04
    void* unknown;        // +0x08 (possibly parent or data)
    unsigned int key;     // +0x0C
    // ... padding to 0x25
    char sentinelFlag;    // +0x25 (non‑zero if sentinel/leaf)
};

struct FindInsertResult {
    TreeNode* parentOrThis; // first output pointer (contextual)
    TreeNode* node;         // second output pointer
    char insertedFlag;      // 1 = new node inserted, 0 = key already exists
};

// Container class with a tree head at +0x1C
class TreeMap {
    TreeNode* treeHead; // +0x1C: points to a sentinel node (left child = root, right child = sentinel)
    // ... other members

public:
    FindInsertResult* findOrInsert(unsigned int* key, FindInsertResult* result);
};

// Forward declarations of helper functions (assumed to exist elsewhere)
TreeNode* insertNode(TreeMap* this, TreeNode** insertPos, int insertDirection, unsigned int* key);
void rebalanceAfterInsert(void); // fixes tree balance after insertion

FindInsertResult* TreeMap::findOrInsert(unsigned int* key, FindInsertResult* result) {
    TreeNode* current = this->treeHead; // head sentinel
    bool wentRight = true; // indicates branch taken when traversing

    // Check if tree is non‑empty: the sentinel node's right child has sentinelFlag==0 means real node?
    if (*(char*)((int)current->right + 0x25) == '\0') {
        // Traverse tree to find insertion point
        TreeNode* child = current->right;
        do {
            current = child;
            if (*key < current->key) {
                child = current->left;   // go left
            } else {
                wentRight = true;        // note: actually wentRight stays true?
                child = current->right;  // go right
            }
        } while (*(char*)((int)child + 0x25) == '\0'); // continue while not sentinel
    }

    // The result will be stored here (this pointer passed as extra)
    TreeMap* insertContext = this;

    if (wentRight) { // always true after traversal
        // If we are at the root node (which is the left child of head sentinel)
        if (current == *(TreeNode**)this->treeHead->left) {
            // Need to insert a new root? Insert as left child of sentinel?
            TreeNode* newNode = insertNode(this, &insertContext, 1, key);
            result->parentOrThis = newNode;       // first field is new node?
            result->node = *(TreeNode**)((int)newNode + 4); // second field from inserted?
            result->insertedFlag = 1;
            return result;
        }
        // Otherwise, the tree may need rebalancing after insertion
        rebalanceAfterInsert();
    }

    // Now compare key with current node
    if (current->key < *key) {
        // Key not found, insert new node to the right (or left depending on previous traversal)
        TreeNode* newNode = insertNode(this, &insertContext, wentRight, key);
        result->parentOrThis = newNode;       // first output
        result->node = *(TreeNode**)((int)newNode + 4);
        result->insertedFlag = 1;
        return result;
    }

    // Key already exists in the tree
    result->parentOrThis = (TreeNode*)this; // return this pointer as context
    result->node = current;                 // the found node
    result->insertedFlag = 0;
    return result;
}