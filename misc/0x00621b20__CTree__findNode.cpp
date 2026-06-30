// FUNC_NAME: CTree::findNode
// Function address: 0x00621b20
// This function performs a binary search tree lookup for a uint key.
// It traverses the tree starting from the root (stored at this+0x1c) and
// returns the node matching the key or the leaf sentinel (flag non-zero).
// Output is written to an array of two pointers pointed to by EAX:
// out[0] = this, out[1] = found node or leaf.

#include <cstdint>

class CTree {
public:
    struct TreeNode {
        uint32_t left;      // +0x00: left child (or sentinel)
        uint32_t right;     // +0x04: right child (or sentinel)  
        uint32_t key;       // +0x08: key value
        uint32_t field0x0C; // +0x0C: unused?
        // ... layout continues up to offset 0x25
        uint8_t  isLeaf;    // +0x25: !=0 if leaf node
    };

    // +0x1C: pointer to header node (root stored at header->right)
    TreeNode* m_pHeader;  
};

void __fastcall CTree::find(uint32_t key, TreeNode** out) {
    // out is in EAX (undefined4 *in_EAX)
    TreeNode* current = this->m_pHeader;         // puVar3
    TreeNode* leafNode;                           // puVar1

    if (*(uint8_t*)(current->right + 0x25) == 0) { // root is not a leaf?
        leafNode = (TreeNode*)current->right;       // start from right child
        do {
            if (leafNode->key < key) {
                leafNode = (TreeNode*)leafNode->right; // move right
            } else {
                TreeNode* tmp = (TreeNode*)leafNode->left;
                current = leafNode;      // update last non-leaf where we went left
                leafNode = tmp;
            }
        } while (*(uint8_t*)((int)leafNode + 0x25) == 0); // while not leaf
    } else {
        leafNode = (TreeNode*)current->right;
    }

    // Determine which node to return
    if (current != this->m_pHeader && current->key <= key) {
        out[0] = this;
        out[1] = current;
    } else {
        out[0] = this;
        out[1] = leafNode;
    }
    return;
}