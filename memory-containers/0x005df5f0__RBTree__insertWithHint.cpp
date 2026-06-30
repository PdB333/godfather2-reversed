// FUNC_NAME: RBTree::insertWithHint
// Function address: 0x005df5f0
// Inserts a new node into a red-black tree near a hint node.
// Uses a standard RB-tree insert then rebalance (left/right rotations, color flips).
// Known EA STL container (map/set). Parameters: this (ECX), hint node (EDI), insert direction, output pair.

struct RBTreeNode {
    RBTreeNode* left;       // +0x00
    RBTreeNode* right;      // +0x04
    RBTreeNode* parent;     // +0x08
    void* value;            // +0x0C (optional, not used here)
    unsigned char blackFlag; // +0x14 (1 = black, 0 = red)
    unsigned char unused;    // +0x15
};

struct RBTree {
    void* header; // +0x1C: pointer to header node (sentinel, with leftmost, rightmost, root)
    int size;      // +0x20
};

// Header node equivalents (offsets 0,4,8):
// header->leftmost = smallest element
// header->rightmost = largest element
// header->parent = root of tree

// Pair structure: result[0] = tree, result[1] = new node
typedef int* Pair; // simplified output (two ints)

// Forward declaration of helper functions (from other places)
RBTreeNode* allocateNode();                          // FUN_005e0110
void throwLengthError(const char* msg, int code);    // FUN_0043f9f0
void rotateLeft(RBTree* tree, RBTreeNode* x);       // FUN_005df960 (actually performs left rotation)
void freeStringBuffer(void* buf);                    // FUN_009c8eb0

void RBTree::insertWithHint(RBTreeNode* hintNode, bool insertLeft, Pair& result)
{
    // Validate size
    if (size > 0x1FFFFFFD) {
        uint local28 = 0xF;
        int local2c = 0;
        uint local3c = 0;
        throwLengthError("map/set<T> too long", 0x13);
        // exception handling epilogue (omitted)
    }

    // Allocate a new node
    RBTreeNode* newNode = allocateNode();
    size++;

    // Decide insertion position relative to hintNode and header
    RBTreeNode* headerNode = *(RBTreeNode**)(this + 0x1C);

    if (hintNode == headerNode) {
        // Insert into empty tree or at end
        headerNode->rightmost = newNode;  // +0x04
        headerNode->leftmost = newNode;   // +0x00
        headerNode->parent = newNode;     // +0x08 (root)
    }
    else if (insertLeft == 0) {
        // Insert before hintNode
        hintNode->parent = newNode;       // +0x08
        if (hintNode == headerNode->rightmost) {
            headerNode->rightmost = newNode;
        }
    }
    else {
        // Insert after hintNode
        hintNode->left = newNode;          // +0x00
        if (hintNode == headerNode->leftmost) {
            headerNode->leftmost = newNode;
        }
    }

    // Now rebalance the tree (standard RB fixup)
    newNode->blackFlag = 0; // new node is red
    RBTreeNode* current = newNode;
    while (current->parent->blackFlag == 0) { // while parent is red
        RBTreeNode* parent = current->parent;
        RBTreeNode* grandparent = parent->parent;

        if (parent == grandparent->left) {
            RBTreeNode* uncle = grandparent->right;
            if (uncle && uncle->blackFlag == 0) {
                // Case 1: uncle is red, flip colors
                parent->blackFlag = 1;
                uncle->blackFlag = 1;
                grandparent->blackFlag = 0;
                current = grandparent;
                continue;
            }
            if (current == parent->right) {
                // Case 2: current is right child, rotate left
                rotateLeft(this, parent);
                current = parent;
                parent = current->parent;
            }
            // Case 3: rotate right and recolor
            parent->blackFlag = 1;
            grandparent->blackFlag = 0;
            rotateRight(this, grandparent);
        }
        else {
            // Symmetric: parent is right child of grandparent
            RBTreeNode* uncle = grandparent->left;
            if (uncle && uncle->blackFlag == 0) {
                parent->blackFlag = 1;
                uncle->blackFlag = 1;
                grandparent->blackFlag = 0;
                current = grandparent;
                continue;
            }
            if (current == parent->left) {
                rotateRight(this, parent);
                current = parent;
                parent = current->parent;
            }
            parent->blackFlag = 1;
            grandparent->blackFlag = 0;
            rotateLeft(this, grandparent);
        }
    }
    // Ensure root is black
    headerNode->parent->blackFlag = 1;

    // Set output pair
    result[0] = (int)this;
    result[1] = (int)newNode;
    return;
}