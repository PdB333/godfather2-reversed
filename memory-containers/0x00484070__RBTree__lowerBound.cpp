// FUNC_NAME: RBTree::lowerBound

// Node structure (binary search tree node with sentinel leaf markers)
// +0x00 : RBTreeNode* left
// +0x04 : RBTreeNode* parent (unused in this function)
// +0x08 : RBTreeNode* right
// +0x0C : uint32_t key
// +0x15 : uint8_t sentinelFlag (0 = sentinel node, non-zero = real node)

// Header structure accessed at this+4
// +0x00 : uint32_t someField
// +0x04 : RBTreeNode* root

struct RBTreeNode {
    RBTreeNode* left;
    RBTreeNode* parent;
    RBTreeNode* right;
    uint32_t   key;
    uint8_t    sentinelFlag;   // 0 indicates sentinel (leaf), non-zero indicates valid node
};

struct RBTreeHeader {
    uint32_t    unk0;
    RBTreeNode* root;
};

struct RBTreeIterator {
    RBTree*     tree;
    RBTreeNode* node;
};

void RBTree::lowerBound(uint32_t key, RBTreeIterator& result) const
{
    // Fetch the internal header from this+4
    RBTreeHeader* header = *(RBTreeHeader**)((uint8_t*)this + 4);
    RBTreeNode*   root   = header->root;

    RBTreeNode* current   = root;
    RBTreeNode* candidate = root;

    // Only traverse if the tree is non‑empty (root is not a sentinel)
    if (root->sentinelFlag == 0) {
        do {
            if (current->key < key) {
                // Move right – no candidate update
                current = current->right;
            } else {
                // Move left – save this node as the best candidate so far
                candidate = current;
                current   = current->left;
            }
        } while (current->sentinelFlag == 0);
        // Loop exits when we have reached a sentinel node
    }

    // If a valid candidate exists and its key is ≤ the search key, use it
    if (candidate != root && candidate->key <= key) {
        result.tree = this;
        result.node = candidate;
    } else {
        // Otherwise return the last visited node (or root if tree was empty)
        result.tree = this;
        result.node = current;
    }
}