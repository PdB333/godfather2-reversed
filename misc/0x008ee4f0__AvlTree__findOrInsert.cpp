// FUNC_NAME: AvlTree::findOrInsert
// Address: 0x008ee4f0
// Role: Search for a key in an AVL-like tree, returning the node if found or inserting a new node if not.
// This is a classic "find or insert" operation for a balanced binary search tree (likely AVL or RB).

struct AvlTree;
struct AvlNode;

// Node layout (inferred from decompiled offsets):
// +0x00: AvlNode* leftChild
// +0x04: AvlNode* rightChild? Or parent? Actually used as start of traversal.
// +0x08: AvlNode* rightChild? Actually used as right child.
// +0x0C: unsigned int key
// +0x19: char isSentinel; // 0 = real node; non-zero = leaf/sentinel

// Output structure for findOrInsert result
struct FindResult {
    AvlTree* tree;   // +0x00
    AvlNode* node;   // +0x04
    char inserted;   // +0x08: 0 = found, 1 = inserted
};

void __thiscall AvlTree::findOrInsert(AvlTree* this, FindResult* outResult, unsigned int* key) {
    AvlNode* currentNode;
    AvlNode* nextNode;
    bool goLeft;

    // Get the root node from the tree (offset +0x04 is a pointer to the root)
    currentNode = *(AvlNode**)((int)this + 4);
    goLeft = true;

    // Check if the tree is not empty (the root's sentinel at +0x19 is zero)
    if (currentNode->isSentinel == 0) {
        // Traverse the tree to find the insertion point
        currentNode = currentNode;
        do {
            // Compare the target key with the current node's key
            if (*key < currentNode->key) {
                // Go left
                nextNode = currentNode->leftChild;
            } else {
                // Go right (or equal; if equal, we stop later)
                nextNode = currentNode->rightChild;  // index 2 (offset +0x08)
            }
            currentNode = nextNode;
        } while (currentNode->isSentinel == 0);
    }

    // At this point, currentNode points to a sentinel node (or the root if empty)
    // Check if we found an existing node with the same key
    if (goLeft) {
        // If we ended up at the leftmost sentinel (i.e., the tree root was a sentinel), set flag
        if (currentNode == *(AvlNode**)(*(int*)this + 4)) { // Check if it's the end of traversal? Actually this checks if currentNode is the root's left child? Complex.
            goLeft = true;
            goto done;
        }
        // If not, we need to insert? Actually call a helper that might rebalance.
        FUN_008ea610(); // Likely rebalance or adjust
    }

    // Compare key with node's key
    if (*key <= currentNode->key) {
        // Key already exists (or insert at this point? Actually <= indicates we found the node)
        outResult->tree = this;
        outResult->node = currentNode;
        outResult->inserted = 0; // found existing
        return;
    }

done:
    // Key not found; insert new node via FUN_008ed3e0
    FindResult tempResult;
    AvlNode* insertedNode = FUN_008ed3e0(&tempResult, goLeft, currentNode, key);
    outResult->tree = tempResult.tree;
    outResult->node = insertedNode; // Actually tempResult.node
    outResult->inserted = 1; // inserted new node
    return;
}