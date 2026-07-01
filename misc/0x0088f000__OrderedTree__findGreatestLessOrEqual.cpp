// FUNC_NAME: OrderedTree::findGreatestLessOrEqual
//
// Function at 0x0088f000: Binary search tree floor lookup.
// Searches for the greatest key <= searchKey and returns the corresponding node.
// Tree nodes are arranged such that left child (offset 0x00) holds keys greater than node.key,
// and right child (offset 0x04) holds keys less than or equal to node.key.
// The tree container has an embedded sentinel node at offset 0x04 from 'this',
// and a root pointer at offset 0x0c.

#include <cstdint>

// Node structure – offsets relative to node base:
// +0x00: TreeNode* leftChild (used when node.key < searchKey)
// +0x04: TreeNode* rightChild (used otherwise, also stores candidate)
// +0x08: (unknown, possibly parent)
// +0x0c: (unknown)
// +0x10: uint32_t key
struct TreeNode {
    TreeNode*         left;      // +0x00
    TreeNode*         right;     // +0x04
    // 8 bytes of padding / other fields
    uint32_t          key;       // +0x10

    // Accessor for the unknown fields if needed
};

class OrderedTree {
public:
    // Search for the node with greatest key <= searchKey.
    // Returns a pointer to the node, or the sentinel if none exists.
    TreeNode* findGreatestLessOrEqual(uint32_t searchKey) const {
        // sentinel located at this+4 (embedded node)
        TreeNode* sentinel = reinterpret_cast<TreeNode*>(
            reinterpret_cast<const uint8_t*>(this) + 4);
        // root pointer at this+0xc
        TreeNode* cur = *reinterpret_cast<TreeNode* const*>(
            reinterpret_cast<const uint8_t*>(this) + 0x0c);
        TreeNode* best = sentinel;

        while (cur != nullptr) {
            if (cur->key < searchKey) {
                // Go left (this branch leads to even larger keys)
                cur = cur->left;
            } else {
                // This node is a candidate; go right (smaller keys)
                best = cur;
                cur = cur->right;
            }
        }

        // If the best candidate is not the sentinel and its key is within range,
        // return it; otherwise return the sentinel.
        if (best != sentinel && best->key <= searchKey) {
            return best;
        } else {
            return sentinel;
        }
    }
};