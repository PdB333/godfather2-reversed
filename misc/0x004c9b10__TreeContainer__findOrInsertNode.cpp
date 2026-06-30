// FUNC_NAME: TreeContainer::findOrInsertNode
int* __thiscall TreeContainer::findOrInsertNode(void* tree, int* output, uint* keyPtr)
{
    // tree at param_1, likely a container object
    // output is a 3-field structure: {void* parentOrNode; void* nodeOrLeaf; bool insertedOrFound}
    // keyPtr: pointer to key to search for

    // The container uses an intrusive binary search tree with a header node.
    // The header node is stored as a pointer at tree+0x1c.
    // The header's right child is the root of the tree.
    // The header's left child points to the minimum node in the tree (for quick access).

    Node* header = *(Node**)((char*)tree + 0x1c);  // +0x1c: header node pointer
    bool goLeft = true; // direction from parent to child in last step
    Node* parent = header; // node whose child we're about to follow next

    // If the root exists (header->right is not a leaf), traverse the tree
    if (*((char*)header->right + 0x15) == '\0')  // +0x15: leaf flag (0 = internal, non-zero = leaf)
    {
        Node* current = header->right; // start from root

        do {
            parent = current;
            goLeft = (*keyPtr < current->key);    // +0x0c: key field
            if (goLeft) {
                current = current->left;          // +0x00: left child
            } else {
                current = current->right;         // +0x04: right child
            }
        } while (*((char*)current + 0x15) == '\0');
    }

    // After the loop, "parent" is the node above a leaf (or header if tree empty)
    // goLeft indicates whether we went left from parent to reach that leaf

    // Special case: if we are supposed to go left and parent is the minimum node (header->left)
    if (goLeft) {
        if (parent == header->left)  // header->left is the minimum node pointer
        {
            // Insert a new node as the left child of parent (i.e., new minimum)
            int* result = TreeContainer::insertNodeInternal(tree, &parent, 1, keyPtr);
            output[0] = result[0];
            output[1] = result[1];
            *(unsigned char*)(output + 2) = 1; // inserted
            return output;
        }
        // If parent is not the minimum, something is inconsistent – assert
        TreeContainer::debugAssert();
    }

    // Determine if we need to insert or if key already exists
    if (parent->key < *keyPtr)  // +0x0c: key field
    {
        // Key greater than parent's key, go right
        int* result = TreeContainer::insertNodeInternal(tree, &parent, goLeft, keyPtr);
        output[0] = result[0];
        output[1] = result[1];
        *(unsigned char*)(output + 2) = 1; // inserted
        return output;
    }

    // Key found: parent->key == *keyPtr
    output[0] = (int)tree;          // container pointer
    output[1] = (int)parent;        // the node containing the key
    *(unsigned char*)(output + 2) = 0; // not inserted, existing node
    return output;
}