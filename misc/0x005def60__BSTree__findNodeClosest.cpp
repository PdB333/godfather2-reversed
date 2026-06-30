// FUNC_NAME: BSTree::findNodeClosest
void BSTree::findNodeClosest(uint *param_1)
{
    // this in ESI, param_1 is uint* key
    BSTNode *root = *(BSTNode **)(this + 0x1c); // +0x1c: root node pointer
    BSTNode *node = root;
    BSTNode *closest = root;

    // traverse while node has a valid flag (character at offset 0x15 from node->name is null)
    if (node != nullptr && node->name[0x15] == '\0') {
        do {
            if (node->key < *param_1) {
                // go right (offset 0x08)
                node = node->right;
            } else {
                // go left (offset 0x00) and remember as closest
                node = node->left;
                closest = node; // actually the current node before moving is stored, but logic: if key <=, keep current as closest
                // Original: puVar2 = *puVar1; puVar3 = puVar1; so puVar3 becomes the node before going left
                // Reconstructed: if key >= param, go left and set closest = current node (puVar3)
            }
        } while (node != nullptr && node->name[0x15] == '\0');
    }

    // After traversal, check if closest is different from root and its key <= input
    if (closest != root && closest->key <= *param_1) {
        *this = (uint)this; // in_EAX[0] = this; in_EAX[1] = closest
        return; // Return struct via EAX/EDX
    }

    // Otherwise return root as default
    *this = (uint)this;
    return; // Return (this, root)
}