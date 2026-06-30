// FUNC_NAME: TreeFind (binary search tree node lookup)
// Function address: 0x00573db0
// Role: Searches a binary search tree for a node matching a key value.
//   Uses node layout:
//     +0x08: Node* left
//     +0x0C: Node* right
//     +0x10: int key
//   The search returns the node (or nullptr) via the return value.

Node* __fastcall TreeFind(Node* root, int key) {
    Node* found = nullptr;
    Node* current = root;

    while (current != nullptr && found == nullptr) {
        if (key < current->key) {
            // Go left
            current = current->left;          // +0x08
        } else {
            found = current;
            if (current->key < key) {
                // Go right, reset found
                current = current->right;     // +0x0C
                found = nullptr;
            }
            // else: keys equal, found remains current
        }
    }

    return found;
}