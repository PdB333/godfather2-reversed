// FUNC_NAME: Tree::lowerBound
// 0x005def60: Binary search tree lower bound search (EARS engine)
// Returns the first node with key >= given key, or the sentinel (end) if none.
// Write result to output buffer: result[0] = this, result[1] = node pointer.
// Node layout (offsets):
// +0x00: left child (Node*)
// +0x04: (unused in traversal)
// +0x08: right child (Node*)
// +0x0C: key (uint)
// +0x15: leaf flag (non-zero = leaf/sentinel)

void __thiscall Tree::lowerBound(const uint &key, Node **result) {
    // this+0x1c: pointer to root node (or header node)
    Node *root = *(Node**)((char*)this + 0x1c);
    // Start traversal from the right child of root (or directly from root's sentinel).
    // In this implementation, root->field at +0x04 (index [1]) points to the first node.
    Node *cur = (Node*)((uint*)root)[1]; // root->childOrHeaderField

    // Check if the starting node is already a leaf (leaf flag non-zero).
    // If yes, the tree is effectively empty (skip search).
    if (*(char*)((int)cur + 0x15) == '\0') {
        Node *parent = root; // will hold the last non-leaf node visited

        do {
            // Compare current node's key with the target key
            if (cur->key < key) {
                // Go right
                cur = cur->right;
            } else {
                // Go left, remember this node as potential result
                cur = cur->left;
                parent = cur;
            }
        } while (*(char*)((int)cur + 0x15) == '\0'); // continue until leaf

        // parent is the deepest non-leaf node that went left (i.e., candidate lower bound)
        // If parent is not the root and its key <= key, it is the result.
        if (parent != root && parent->key <= key) {
            result[0] = (Node*)this;
            result[1] = parent;
            return;
        }
    }

    // No valid lower bound found – return the sentinel (end) node.
    result[0] = (Node*)this;
    result[1] = root;
}