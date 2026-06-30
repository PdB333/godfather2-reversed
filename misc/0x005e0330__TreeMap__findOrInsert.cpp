// FUNC_NAME: TreeMap::findOrInsert
// Address: 0x005e0330
// Searches a binary search tree (with sentinel header) for a key.
// Returns an iterator (container pointer + node pointer) and a bool indicating if insertion occurred.
// Node layout (offsets):
//   +0: left child
//   +4: parent
//   +8: right child
//   +12: key (uint32)
//   +0x15: sentinel flag (0 = sentinel/leaf, non-zero = real node)

struct TreeNode {
    TreeNode* left;   // +0
    TreeNode* parent; // +4
    TreeNode* right;  // +8
    uint32_t key;     // +12
    // padding/extra fields
    uint8_t sentinelFlag; // +0x15 (21)
};

struct TreeMap {
    // Offset 0x1c: pointer to the sentinel header node (not the real root)
    TreeNode* header; // sentinel node
};

// Internal insertion helper – returns a pair (container pointer, new node pointer)
int* treeInsert(TreeMap* self, TreeNode** parentPtr, int direction, uint32_t* key);
void treeAssert(); // likely an assertion

__thiscall int* TreeMap::findOrInsert(int* thisPtr, int* outResult, uint32_t* inKey) {
    TreeMap* self = (TreeMap*)thisPtr;
    TreeNode* header = self->header;
    TreeNode* current = header->parent; // real root of the tree (starts with sentinel's parent)
    bool goLeft = true;

    // If the tree is non-empty (root is not a sentinel), traverse to find insertion point
    if (current->sentinelFlag == 0) {
        do {
            // Actually start traversal from header->parent (the root)
            // The code initializes a temporary node from header->parent and then loops
            // Reconstructed loop from decompiled:
            //   puVar2 = header->parent
            //   do {
            //       current = puVar2;
            //       goLeft = *inKey < current->key;
            //       puVar2 = goLeft ? current->left : current->right;
            //   } while (puVar2->sentinelFlag == 0);
            // But the decompiled code used local_4 for current and puVar2 for next.
            // Simpler: traverse until we reach a leaf (sentinel)
            while (current->sentinelFlag != 0) { // sentinelFlag non-zero means real node? Actually the condition checks == '\0' to continue.
                goLeft = (*inKey < current->key);
                if (goLeft) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
        } while (false); // Actually the do-while was around the inner loop? The decompiled code was odd.
    }

    // After traversal, if we never entered the loop (tree empty), goLeft remains true.
    // If goLeft and we are at the leftmost leaf, insert as first element.
    if (goLeft) {
        // Check if current equals the header's left child (i.e., the minimum node in the tree)
        if (current == header->left) {
            TreeNode* parent = (TreeNode*)thisPtr; // local_8 was set to this
            // Insert as the first node (direction 1)
            int* insertResult = treeInsert(self, &parent, 1, inKey);
            outResult[0] = insertResult[0];
            outResult[1] = insertResult[1];
            *((uint8_t*)(outResult + 2)) = 1; // inserted
            return outResult;
        }
        treeAssert(); // This branch should not happen – would be an internal error
    }

    // Now check if the key is greater than the current node's key (i.e., we went right)
    if (current->key < *inKey) {
        // Insert after current: direction 0 (or false)
        TreeNode* parent = (TreeNode*)thisPtr;
        int* insertResult = treeInsert(self, &parent, 0, inKey);
        outResult[0] = insertResult[0];
        outResult[1] = insertResult[1];
        *((uint8_t*)(outResult + 2)) = 1; // inserted
        return outResult;
    }

    // Key already exists – return found iterator
    outResult[0] = (int)thisPtr;          // container pointer
    outResult[1] = (int)current;          // node pointer
    *((uint8_t*)(outResult + 2)) = 0;     // not inserted
    return outResult;
}