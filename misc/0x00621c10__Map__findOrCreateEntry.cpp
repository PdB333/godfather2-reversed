// FUNC_NAME: Map::findOrCreateEntry
// Reconstructed from 0x00621c10: find or create node with given key in a binary tree (likely a map)
// The tree nodes have left (0x00), parent (0x04), right (0x08), key (0x0C), and a byte flag (0x15)
// The header node at +0x1c contains the root in its parent field (0x04)

typedef unsigned int uint;

// Tree node structure (16 bytes header + flag byte, then data? but we only need to traverse)
struct TreeNode {
    TreeNode* left;      // +0x00
    TreeNode* parent;    // +0x04
    TreeNode* right;     // +0x08
    uint key;            // +0x0C
    // byte at +0x15: 0 = internal node, non-zero = sentinel (leaf)
};

// Insertion helper (external, not defined here)
TreeNode* insertNode(Map* map, void* buffer, uint* key, TreeNode* hint);

// This is a member function of some map class
// The class holds a pointer to a header node at offset 0x1c
undefined4* Map::findOrCreateEntry(uint* param_1)
{
    TreeNode* currentHeader = *(TreeNode**)((uint)this + 0x1c); // header node
    TreeNode* current = reinterpret_cast<TreeNode*>(currentHeader->parent); // root from header's parent field

    // If root is not a sentinel (i.e., the tree exists)
    if (current && *(char*)((uint)current + 0x15) == '\0') {
        TreeNode* node;
        do {
            if (current->key < *param_1) {
                node = current->right;
            } else {
                node = current->left;
                currentHeader = current; // track the last node before the sentinel
            }
            current = node;
        } while (node && *(char*)((uint)node + 0x15) == '\0');
    }

    // If we didn't find the key (either tree empty or went to sentinel)
    if (currentHeader == *(TreeNode**)((uint)this + 0x1c) || *param_1 < currentHeader->key) {
        uint keyVal[2] = { *param_1, 0 }; // key to insert
        int* result = (int*)insertNode(this, (void*)0, keyVal, (uint)this, currentHeader);
        // Note: the inserted node is returned via result and currentHeader is updated
        currentHeader = (TreeNode*)result[1];
    }

    // Sanity checks (debug assertions)
    if (currentHeader == *(TreeNode**)((uint)this + 0x1c)) {
        // Should not happen: tree empty
        *(uint*)0 = 0;
    }
    if (currentHeader == nullptr) {
        *(uint*)0 = 0;
    }

    // Return pointer to the data area (after node header)
    return (undefined4*)((uint)currentHeader + 0x10);
}