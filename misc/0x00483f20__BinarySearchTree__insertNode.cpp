// FUNC_NAME: BinarySearchTree::insertNode
// Function address: 0x00483f20
// Inserts a key into a binary search tree. Searches from root, creates new node if key not found.
// Output is stored in a result structure pointed by EDI (caller provides via register).

struct BSTNode {
    BSTNode* left;      // +0x00
    void* data;         // +0x04  // Pointer to associated data object
    BSTNode* right;     // +0x08
    uint32_t key;       // +0x0C
};

struct DataNode {
    char pad0[0x15];
    char isTerminator; // +0x15  // 0 = active node, non-zero = sentinel
};

struct InsertResult {
    BSTNode* parent;    // +0x00
    BSTNode* child;     // +0x04
    bool inserted;      // +0x08  // 1 if new node was created, 0 if key already existed
};

// External functions
BSTNode* BST_AllocateNode(int param_1, BSTNode* parent, bool goLeft, BSTNode* current, uint32_t* key);
void BST_AssertFailed(); // FUN_00484ec0

void BinarySearchTree::insertNode(BSTNode* root, uint32_t* key, InsertResult* result) {
    // root is at this + 0x04; param_1 is this pointer, param_2 is key pointer
    BSTNode* current = root;
    bool goLeft = true;

    // If the root's data node is not a sentinel, traverse the tree
    if (static_cast<DataNode*>(current->data)->isTerminator == 0) {
        BSTNode* next;
        do {
            current = next;
            goLeft = *key < current->key;
            next = goLeft ? current->left : current->right;
        } while (static_cast<DataNode*>(next->data)->isTerminator == 0);
    }

    BSTNode* parent = root;
    BSTNode* child = current;

    if (goLeft) {
        // If we need to go left, check if we are at the actual root (sentinel)
        if (current == root->left) { // root->left points to sentinel? Actually root is the sentinel?
            // Need to insert new node at the root level
            // The comparison checks if current == root->left? But root->left might be sentinel
            // For simplicity, treat as special case
            BSTNode* newNode = BST_AllocateNode(this, &parent, 1, current, key);
            result->parent = newNode;
            result->child = newNode;
            result->inserted = true;
            return;
        }
        BST_AssertFailed();
    }

    // After traversal, compare key with current node's key
    if (child->key < *key) {
        BSTNode* newNode = BST_AllocateNode(this, &parent, goLeft, current, key);
        result->parent = newNode;
        result->child = newNode;
        result->inserted = true;
        return;
    }

    // Key already exists; return the existing node
    result->parent = parent;
    result->child = child;
    result->inserted = false;
}