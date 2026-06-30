// FUNC_NAME: TreeContainer::findNode

#include <cstdint>

// TreeNode structure (determined from decompilation)
// +0x00: left child pointer (TreeNode*)
// +0x04: right child pointer
// +0x08: parent pointer (unused in this function)
// +0x0C: key (uint32_t)
// +0x15: sentinel flag (0 = sentinel/placeholder, non-zero = real node)
struct TreeNode {
    TreeNode* left;       // +0x00
    TreeNode* right;      // +0x04
    TreeNode* parent;     // +0x08 (not used directly)
    uint32_t key;         // +0x0C
    uint8_t sentinelFlag; // +0x15 (byte, 0 means node is a sentinel)
    // padding to align to 4 bytes likely follows
};

// Container class that holds a tree root
// +0x1C: root pointer (TreeNode*)
class TreeContainer {
public:
    TreeNode* root; // +0x1C

    // __thiscall: this passed in ESI, keyPtr in stack, output in EAX (out)
    void __thiscall findNode(uint32_t* keyPtr, TreeNode** outContainer, TreeNode** outNode) {
        TreeNode* current;
        TreeNode* lastLeft = nullptr;

        // Get the tree root
        current = this->root;

        // Check if the right child of the root is a sentinel (i.e., empty tree)
        if (current->right->sentinelFlag == 0) {
            // Start traversal from the sentinel node
            TreeNode* node = current->right;
            do {
                if (node->key < *keyPtr) {
                    // Go right
                    current = node->right;
                } else {
                    // Go left and remember this node as the last left turn
                    lastLeft = node;
                    current = node->left;
                }
                node = current;
            } while (node->sentinelFlag == 0);
        }

        // Re-fetch root (overwrites any previous current from the loop)
        current = this->root;

        // Determine which node to return
        if (lastLeft != current && lastLeft->key <= *keyPtr) {
            // Return the node that was the last left turn (predecessor or exact match)
            *outContainer = this;
            *outNode = lastLeft;
        } else {
            // Return the root (or root's sentinel)
            *outContainer = this;
            *outNode = current;
        }
    }
};