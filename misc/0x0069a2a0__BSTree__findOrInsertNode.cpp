// FUNC_NAME: BSTree::findOrInsertNode
// Address: 0x0069a2a0
// This is a generic binary search tree (BST) insertion/lookup function.
// It searches for a key (param_3) using a comparator (FUN_004d4b20).
// If found, returns the node in *result with flag false.
// If not found, inserts a new node (via FUN_00699df0) and returns the new node with flag true.

struct BSTNode {
    BSTNode* left;      // +0x00
    BSTNode* right;     // +0x04
    // key data follows at +0x08
};

struct BSTree {
    BSTNode* sentinel;  // +0x04 - dummy sentinel node or similar
    BSTNode* end;       // +0x08 - maybe pointer to rightmost leaf? or something
    BSTNode* root;      // +0x0C
};

// External functions
int __fastcall BSTreeCompare(BSTNode* node, uint32_t key);          // FUN_004d4b20 - returns <0 if node key < key, >0 if greater, 0 if equal
BSTNode* __fastcall BSTreeGetPrev(BSTNode* node);                   // FUN_00ab3c90 - returns predecessor node in the tree
void __fastcall BSTreeInsert(BSTNode* parent, BSTNode* newChild, uint32_t key); // FUN_00699df0 - inserts newChild under parent with given key

void __thiscall BSTree::findOrInsertNode(BSTree* thisPtr, Pair<BSTNode*, bool>* result, uint32_t key)
{
    BSTNode* current;
    BSTNode* parent;
    bool wentLeft;
    int cmp;

    wentLeft = false;
    current = thisPtr->root;            // start at root
    parent = thisPtr->sentinel;         // parent starts at sentinel

    // Standard BST traversal
    while (current != nullptr) {
        cmp = BSTreeCompare(current, key);
        wentLeft = (cmp < 0);           // if key < current key, go left
        parent = current;
        if (wentLeft) {
            current = current->right;   // note: left branch goes right? Actually cmp<0 means go right? Wait, typical: if key < node, go left. But here it's reversed? The code uses puVar4[1] (right) when cmp < 0, and *puVar4 (left) otherwise. So cmp < 0 means go to right child.
        } else {
            current = current->left;    // cmp >= 0: go left child
        }
    }

    // After traversal, parent is the node where insertion should happen
    current = parent;

    if (wentLeft) {
        // Last move was to the right child (since wentLeft true means we went right)
        if (parent == thisPtr->end) {   // parent reached the end sentinel? 
            // Insert as leftmost? The code compares with +0x8 which might be the rightmost leaf.
            BSTreeInsert(&key, parent, key, 0); // The 0 might be "insert as left child"? 
            result->node = key;         // Actually param_3 (key) is overwritten? This is odd.
            result->found = true;
            return;
        }
        current = BSTreeGetPrev(parent); // get predecessor of parent
    }

    cmp = BSTreeCompare(current, key);
    if (cmp < 0) {
        BSTreeInsert(&key, parent, key, 0);
        result->node = key;
        result->found = true;
        return;
    }

    // Node already exists
    result->node = current;
    result->found = false;
    return;
}