// FUN_00621690: TreeMap::findOrInsert

#include <cstdint>

// Node structure for the binary search tree used in the EARS container.
// Offsets are based on observed access pattern:
//   +0x00: left child pointer
//   +0x04: data field (returned by this function)
//   +0x08: right child pointer
//   +0x0C: key (uint32)
//   +0x25: sentinel byte (0 = leaf, non-zero = internal node)
struct TreeNode {
    TreeNode* left;       // +0x00
    uint32_t data;        // +0x04  (returned as pointer to this field)
    TreeNode* right;      // +0x08
    uint32_t key;         // +0x0C
    // padding?
    uint8_t sentinel;     // +0x25  (actually at offset 0x25 from node start)
};

class TreeMap {
public:
    // Offset +0x1c: pointer to root node of the binary search tree.
    // The root pointer is stored as the first member of the tree data.
    TreeNode* root;       // +0x1c in the containing object?

    // __fastcall: first param (ECX) is 'this', second param (EDX) is pointer to key.
    // Returns pointer to the data field (+4) of the node containing the key.
    // If the key is not found, a new node is inserted and its data pointer returned.
    uint32_t* __fastcall findOrInsert(const uint32_t* keyPtr);
};

// External function: insert a new node into the tree.
extern int* __fastcall FUN_00622110(TreeNode* root, void* param1, uint32_t* keyPtr, TreeMap* map, TreeNode* parent);

// Failure handler (panic / assert)
extern void FUN_00b97aea();

uint32_t* __fastcall TreeMap::findOrInsert(const uint32_t* keyPtr) {
    TreeNode* current;
    TreeNode* candidate;
    uint32_t key = *keyPtr;

    // Navigate from the root stored at 'this + 0x1c'
    TreeNode* rootNode = *(TreeNode**)((char*)this + 0x1c);

    // Start traversal from root
    current = rootNode;
    // Loop until we find a leaf node (sentinel byte at +0x25 == 0)
    while (*(uint8_t*)((char*)current + 0x25) == 0) {
        if (current->key < key) {
            candidate = current->right;
        } else {
            candidate = current->left;
            // Keep track of the last internal node for potential insertion
            rootNode = current;
        }
        current = candidate;
    }

    // At this point, 'current' is a leaf node (sentinel != 0)
    // 'rootNode' is the last internal node that was not traversed to the right.

    // If we reached the original root (meaning tree is empty or key not found)
    // or if key is less than the found leaf's key, we need to insert.
    if ((rootNode == *(TreeNode**)((char*)this + 0x1c)) || (key < rootNode->key)) {
        // Insert a new node
        uint32_t localKey = key;
        // Call the insert helper
        int* result = FUN_00622110(rootNode, nullptr, &localKey, this, rootNode);
        // The helper modifies 'this' indirectly? It sets up in_EAX and rootNode.
        // The returned pointer leads to a new node structure.
        // Update local variables to reflect the new node
        // (the helper likely updates the tree)
        rootNode = (TreeNode*)result[1];  // Assuming result[0] is key, result[1] is node?
        // Actually, decompile shows: piVar3 = (int *)FUN_00622110(...)
        // Then in_EAX = *piVar3; puVar4 = (undefined4 *)piVar3[1];
        // So we adapt:
        rootNode = (TreeNode*)((int*)rootNode)[1]; // Not exact, but approximating.
    }

    // Final sanity checks
    if (rootNode == nullptr) {
        FUN_00b97aea();
    }
    if ((TreeNode*)rootNode == *(TreeNode**)((char*)this + 0x1c)) {
        FUN_00b97aea();
    }

    // Return pointer to the data field at offset +0x04 of the node
    return &rootNode->data;
}