// FUNC_NAME: Tree::findOrInsert
// Reconstructed tree search/insert function. Searches for a key in a binary search tree.
// If not found, inserts a new node. Returns a result struct with node, parent, and found flag.
// The tree uses a sentinel node at this+0x1c. Nodes have: left (0x00), right (0x08), parent? (0x04), key (0x0c), leaf flag (0x15).

struct TreeNode {
    TreeNode* left;      // +0x00
    void* dataOrParent;  // +0x04  (seems to point to a structure with leaf flag at +0x15)
    TreeNode* right;     // +0x08
    int key;             // +0x0c
    // Possibly more data; leaf flag byte at +0x15 is within the data pointed by +0x04?
    // But code also checks leaf flag on node pointers directly, so node includes flag at +0x15.
    char flag[0x16];     // placeholder: byte at +0x15 indicates internal (0) or leaf (non-zero)
};

struct TreeSearchResult {
    TreeNode* parentNode;  // param_2[0]
    TreeNode* currentNode; // param_2[1]
    uint8_t inserted;      // param_2[2] (byte at offset 8)
};

// External functions
void* FUN_004ca230(void* tree, void* parentPtr, bool isLeft, uint* key); // Allocate/insert node
void FUN_004cad70(); // Assert or error

__thiscall
TreeSearchResult* Tree::findOrInsert(void* tree, TreeSearchResult* outResult, uint* key)
{
    TreeNode* rootSentinel = *(TreeNode**)((char*)tree + 0x1c);
    bool goLeft = true; // Direction of last comparison
    TreeNode* current = rootSentinel;

    // Check if root sentinel's data has leaf flag false (internal node)
    if (*(char*)((int)current->dataOrParent + 0x15) == '\0') {
        TreeNode* child;
        do {
            current = child;
            goLeft = *key < current->key;
            if (goLeft) {
                child = current->left;
            } else {
                child = current->right;
            }
        } while (*(char*)((int)child + 0x15) == '\0');  // Continue while child is internal node
    }

    void* parentPtr = tree;  // &local_8, used as pointer to parent variable

    if (goLeft) {
        if (current == rootSentinel) {
            // Insert at root
            TreeNode* newNode = (TreeNode*)FUN_004ca230(tree, &parentPtr, 1, key);
            outResult->parentNode = (TreeNode*)tree;  // parent is the tree itself
            outResult->currentNode = newNode;
            outResult->inserted = 1;
            return outResult;
        }
        // goLeft is true but current is not root -> should not happen normally
        FUN_004cad70();  // Assertion failure
    }

    if (current->key < *key) {
        // Insert as right child
        TreeNode* newNode = (TreeNode*)FUN_004ca230(tree, &parentPtr, goLeft, key);
        outResult->parentNode = (TreeNode*)tree;  // parent is the tree
        outResult->currentNode = newNode;
        outResult->inserted = 1;
        return outResult;
    }

    // Key found
    outResult->parentNode = (TreeNode*)parentPtr;  // parent of current
    outResult->currentNode = current;
    outResult->inserted = 0;
    return outResult;
}