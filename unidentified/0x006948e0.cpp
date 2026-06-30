// FUN_006948e0: BinaryTree::findInsertionParent
// This function traverses the binary tree starting from a sentinel header,
// searching for the parent node of an empty leaf (where byte at +0x25 is zero).
// Returns the parent node that can be used for insertion.
// The comparison function at 0x004d4b20 is used to decide left/right traversal.
// Parameters: this (pointer to tree object), key (value to compare)
// Structure: TreeHeader at this+4 contains two pointers:
//   [0]: pointer to something (unused here)
//   [1]: current traversal node (initially set to root or sentinel)
// Each tree node has:
//   +0x00: left child pointer
//   +0x08: right child pointer
//   +0x25: flag byte (0 = empty slot, non-zero = occupied node)

struct TreeNode {
    TreeNode* left;      // +0x00
    // padding (4 bytes) if pointers are 4 bytes
    TreeNode* right;     // +0x08
    // ... other fields
    char occupiedFlag;   // +0x25
};

struct TreeHeader {
    TreeNode* first;     // +0x00 (unused)
    TreeNode* current;   // +0x04 (initial traversal node)
};

// Declaration of external comparison function (likely returns <0, 0, >0)
int __fastcall compareKey(void* key);

TreeNode* __thiscall BinaryTree::findInsertionParent(void* key) {
    TreeHeader* header = *(TreeHeader**)(this + 4);
    TreeNode* currentNode = header->current;  // puVar5
    TreeNode* parentNode = header;            // puVar2 (initially header)
    
    while (currentNode->occupiedFlag == 0) {
        int cmp = compareKey(key);
        TreeNode* nextNode;
        if (cmp < 0) {
            // Go right (offset +0x08)
            nextNode = currentNode->right;
            // Parent becomes the header? Actually this branch sets puVar5 = puVar2 (parentNode) which is original header.
            // But in code, when cmp < 0, puVar5 is set to puVar2 (parentNode) before updating parentNode?
            // Let's match the original exactly:
            // In the original, when cmp<0: puVar4 = puVar5[2] (current->right), then puVar5 = puVar2 (parentNode)
            // So after this, parentNode is unchanged? Actually code does: puVar5 = puVar2 (which is parentNode at start of iteration).
            // Then parentNode = old puVar5. Hmm.
            // To match, we need temporary.
            // Actually original loop:
            //   puVar4 = (cmp < 0) ? current->right : current->left;
            //   set puVar5 = puVar2? No, code has two separate assignments: 
            //   if (cmp<0) { puVar4 = current->right; puVar5 = parentNode; } else { puVar4 = current->left; }
            //   then parentNode = current; current = puVar4;
            // So it's asymmetric! That suggests that on right branch, it resets current to parentNode? 
            // That seems odd. Let's re-express original decompiled:
            // if (iVar3 < 0) {
            //   puVar4 = (undefined4 *)puVar5[2];
            //   puVar5 = puVar2;
            // }
            // else {
            //   puVar4 = (undefined4 *)*puVar5;
            // }
            // puVar2 = puVar5;
            // puVar5 = puVar4;
            // So for left branch (cmp >=0): puVar4 = *puVar5 (current->left), puVar2 = puVar5, puVar5 = puVar4.
            // For right branch (cmp <0): puVar4 = current->right, then puVar5 = puVar2 (previous parent), then puVar2 = puVar5 (which is now old parent), then puVar5 = puVar4 (right child).
            // This essentially swaps parent and current? Unusual. Possibly it's a bug in decompiler or a special tree structure (like a splay tree?).
            // We'll implement exactly as given.
            nextNode = currentNode->right;
            currentNode = parentNode;  // puVar5 = puVar2 (parentNode)
        } else {
            // Go left (offset +0x00)
            nextNode = currentNode->left;
            // puVar5 remains puVar5? Actually else branch does not reset puVar5, so currentNode stays same? No, after if-else, puVar2 = puVar5; puVar5 = puVar4;
            // So for left: puVar4 = left, then puVar2 = old puVar5 (currentNode), puVar5 = left.
            // So we don't change currentNode before the update.
        }
        parentNode = currentNode;           // puVar2 = puVar5 (old currentNode)
        currentNode = nextNode;             // puVar5 = puVar4
    }
    return parentNode;
}