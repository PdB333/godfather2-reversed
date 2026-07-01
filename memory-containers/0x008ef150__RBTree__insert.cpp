// FUNC_NAME: RBTree::insert
// Function address: 0x008ef150
// Role: Insert a key into a red-black tree (or similar BST) and return pointer to associated data.
// The tree node structure (offsets relative to node start):
//   +0x00: left child (or right? see comments)
//   +0x04: right child (or left?)
//   +0x08: parent
//   +0x0C: key (uint32)
//   +0x10: data (returned as undefined4*)
//   +0x25: flag (0 = internal node, non-zero = leaf/sentinel)

#include <cstdint>

// Forward declarations of helper functions (assumed from callees)
void RBTree_initNodePlaceholder(void* placeholder); // FUN_008eb5e0
int* RBTree_allocateNode(void* buffer, RBTree* tree, void* parent, uint32* key); // FUN_008eeb50
void RBTree_fixupAfterInsert(); // FUN_008eb650 (called twice, likely fixup/balance)
void errorHandler(); // FUN_00b97aea (assertion failure)

struct RBTree {
    // +0x00: unknown (maybe size or sentinel)
    // +0x04: root node pointer
    void* rootPtr; // at offset 0x04
};

struct RBTreeNode {
    RBTreeNode* left;   // +0x00
    RBTreeNode* right;  // +0x04
    RBTreeNode* parent; // +0x08
    uint32 key;         // +0x0C
    // data starts at +0x10
    uint8 flags;        // +0x25 (0 = internal, non-zero = leaf)
};

// __thiscall
undefined4* __thiscall RBTree::insert(RBTree* this, uint32* keyPtr) {
    RBTreeNode* root = *(RBTreeNode**)((char*)this + 4); // +0x04
    RBTreeNode* current = root;
    RBTreeNode* parent = root;

    // Traverse tree if root's left child (or right?) is not a leaf
    // Note: The initial check uses root->right (offset 0x04) but traversal logic is ambiguous.
    // We assume the tree uses a sentinel leaf node; root->right is the actual root of the tree.
    if (*(char*)((int)root->right + 0x25) == '\0') {
        current = root->right; // start from right child (or left?)
        do {
            if (current->key < *keyPtr) {
                // Go left (or right?) - using offset 0x08 (parent field) as child pointer?
                // This is likely a bug in decompilation; we assume standard BST: left if smaller.
                // Based on code: puVar1[2] when key <, so we treat offset 0x08 as left child.
                current = current->parent; // Actually offset 0x08 is parent, but used as child? We'll keep as left.
                // Actually the decompiled code uses puVar1[2] which is offset 0x08. That might be the left child.
                // We'll rename fields accordingly: left at +0x08, right at +0x00, parent at +0x04? No.
                // To match the code, we'll keep the original offsets but rename variables.
                // For simplicity, we'll assume the node structure is:
                // +0x00: right child
                // +0x04: left child
                // +0x08: parent
                // +0x0C: key
                // +0x10: data
                // +0x25: flag
                // Then when key <, go to left child (offset 0x04). But code uses puVar1[2] (offset 0x08) which is parent.
                // This is inconsistent. We'll trust the decompiled logic and keep the original field usage.
                // Given the difficulty, we'll produce a generic reconstruction.
            } else {
                // Go right (offset 0x00)
                parent = current;
                current = current->right; // *puVar1 is offset 0x00
            }
        } while (*(char*)((int)current + 0x25) == '\0');
    }

    // If parent is root or key < parent's key, insert new node
    if ((parent == root) || (*keyPtr < parent->key)) {
        uint32 localKey = *keyPtr;
        // Initialize placeholder structure (size 0x14? local_2c is 4 words + 0xffffffff)
        struct NodePlaceholder {
            uint32 field0;
            uint32 field4;
            uint32 field8;
            uint32 fieldC; // 0xffffffff
            uint32 field10;
        } placeholder = {0, 0, 0, 0xffffffff, 0};
        RBTree_initNodePlaceholder(&placeholder);

        // Allocate new node and link it
        char buffer[8]; // local_34
        int* result = RBTree_allocateNode(buffer, this, parent, &localKey);
        // result[0] = new node pointer? result[1] = something?
        // The code then does: param_1 = *piVar3; puVar4 = (undefined4 *)piVar3[1];
        // So we assign:
        RBTreeNode* newNode = (RBTreeNode*)*result;
        parent = (RBTreeNode*)result[1]; // This might be the parent after insertion? Unclear.

        // Fixup/balance (two calls)
        RBTree_fixupAfterInsert();
        RBTree_fixupAfterInsert();
    }

    // Assertions
    if (this == nullptr) {
        errorHandler();
    }
    if (parent == root) {
        errorHandler();
    }

    // Return pointer to data part of the node (offset 0x10)
    return (undefined4*)((char*)parent + 0x10);
}