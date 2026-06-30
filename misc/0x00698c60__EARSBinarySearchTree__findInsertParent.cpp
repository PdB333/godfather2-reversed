// FUNC_NAME: EARSBinarySearchTree::findInsertParent
// Address: 0x00698c60
// Role: Traverses a binary search tree to find the parent node under which a new node with given key should be inserted.
// Offsets: this+0x04 = dummy parent pointer (sentinel), this+0x0C = root node pointer
// Notes: The comparison function FUN_004d4b20 appears to take only the search key (param_3), but likely also uses the current node's key internally (missing from decompilation). Indicated with comment.

void EARSBinarySearchTree::findInsertParent(KeyType key, Node** outParent) {
    Node* current = *(Node**)(this + 0x0C);  // root
    Node* parent = (Node*)(this + 0x04);     // parent sentinel (dummy node)

    while (current != nullptr) {
        // Compare key with current node's key (comparison function should also receive node key, but decompiled shows only one arg)
        int cmp = FUN_004d4b20(key);  // TODO: actual call likely uses current node's key as second argument (e.g., current->key)
        if (cmp < 0) {
            current = current->left;   // left child at offset 0x00
        } else {
            parent = current;
            current = current->right;  // right child at offset 0x04
        }
    }

    *outParent = parent;  // output the parent node for insertion
}