// FUNC_NAME: Tree_FindOrInsert

struct TreeNode {
    TreeNode* left;     // +0x00
    TreeNode* parent;   // +0x04
    TreeNode* right;    // +0x08
    uint32_t key;       // +0x0C
    // +0x10 maybe color or other
    uint8_t isLeaf;     // +0x15 (0 = internal, non-zero = leaf/sentinel)
};

struct TreeResult {
    TreeNode* parent;  // [0]
    TreeNode* node;    // [1]
    uint8_t found;     // [2] 0 = not found (node points to insert position), 1 = found
};

#define TREE_ANCHOR_OFFSET 0x1C

int* Tree_FindOrInsert(void* tree, TreeResult* result, uint32_t* keyPtr)
{
    TreeNode* anchor = *(TreeNode**)((uint8_t*)tree + TREE_ANCHOR_OFFSET);
    TreeNode* curr = anchor;
    bool wentLeft = true;

    // Traverse to find insertion point if anchor's parent is not a leaf
    if (*(uint8_t*)((uint8_t*)curr->parent + 0x15) == 0) {
        do {
            curr = (wentLeft) ? curr->left : curr->right;
            wentLeft = (*keyPtr < curr->key);
        } while (*(uint8_t*)((uint8_t*)curr + 0x15) == 0);
    }

    // If we went left and reached the anchor's leftmost child (the minimum node)
    if (wentLeft) {
        if (curr == anchor->left) {
            // Insert new node as the new minimum
            result->parent = tree;
            TreeNode* res = Tree_Insert(tree, &result->parent, 1, keyPtr);
            result->node = res;
            result->found = 1;
            return (int*)result;
        }
        // else: should not happen? error?
        Tree_Error();
    }

    // Now curr is the last internal node before leaf
    if (curr->key < *keyPtr) {
        result->parent = tree;
        TreeNode* res = Tree_Insert(tree, &result->parent, wentLeft, keyPtr);
        result->node = res;
        result->found = 1;
        return (int*)result;
    }

    // Key already exists or insertion point found
    result->parent = tree;
    result->node = curr;
    result->found = 0;
    return (int*)result;
}