// FUNC_NAME: BinarySearchTree::findOrInsert

// Function at 0x00696630
// This implements a find-or-insert operation on a binary search tree.
// The tree node structure (offsets relative to node pointer):
// +0x00: left child pointer
// +0x04: ? (unused or parent?)
// +0x08: right child pointer
// +0x0C: key (4 bytes or pointer)
// +0x25: flag (byte: 0 = internal node, non-zero = leaf/sentinel)
// The tree container (this):
// +0x04: pointer to root node

void __thiscall BinarySearchTree::findOrInsert(int this, int *outResult, int key)
{
    char isLeaf;
    int *currentNode;
    int *parentNode;
    int *rootPtr;
    int *leftChild;
    int *rightChild;
    int cmpResult;
    bool goLeft;
    int *newNode;
    int *temp;

    // Get root pointer from container
    currentNode = *(int **)(this + 4);   // dereference this+4 -> root node pointer
    goLeft = true;                        // initial direction (left)

    // Traverse the tree until we reach a leaf node (flag != 0)
    while (true) {
        isLeaf = *(char *)((int)currentNode + 0x25);
        if (isLeaf != 0)
            break;

        // Compare search key with node's key at offset 0x0C
        cmpResult = FUN_004d4b20(currentNode + 3, key); // compare keys
        goLeft = (cmpResult < 0);         // go left if key < node's key, else right

        parentNode = currentNode;          // save parent
        if (goLeft) {
            currentNode = (int *)*currentNode;          // left child at +0x00
        } else {
            currentNode = (int *)currentNode[2];        // right child at +0x08
        }
    }

    // currentNode now points to a leaf node
    // parentNode is the last non-leaf node before the leaf

    int saveThis = this;    // preserve this for potential insertion call
    int *insertParent = parentNode; // parent for insertion

    if (goLeft) {
        // We arrived from the left side
        // Check if parent is the root of the tree (special case)
        // Root is stored at this+4; dereferencing twice gives the root node's left child?
        if (parentNode == (int *)*(int *)*(int **)(this + 4)) {
            // Insert new node as left child of root
            newNode = (int *)FUN_00695f00(&saveThis, 1, parentNode, key);
            outResult[0] = *newNode;       // first field of new node
            outResult[1] = newNode[1];     // second field
            *(char *)(outResult + 2) = 1;  // flag: newly inserted
            return;
        }
        // If parent is not root, we should have taken the other branch? Possibly error.
        FUN_00694060(); // error handler (e.g., "cannot insert duplicate")
    }

    // goLeft is false (we arrived from the right side)
    currentNode = parentNode;   // restore parent as current for next step

    // Compare search key with parent's key? (maybe to check if already present)
    cmpResult = FUN_004d4b20(key);   // single argument? Possibly a comparison with the leaf's key
    if (cmpResult >= 0) {
        // Key found (match) – return existing node
        outResult[0] = saveThis;
        outResult[1] = (int)parentNode;
        *(char *)(outResult + 2) = 0;  // flag: already existed
        return;
    }

    // Key not found – insert new node as right child
    newNode = (int *)FUN_00695f00(&saveThis, 0, parentNode, key);   // 0 = right direction
    outResult[0] = *newNode;
    outResult[1] = newNode[1];
    *(char *)(outResult + 2) = 1;  // flag: newly inserted
    return;
}