// FUNC_NAME: Tree::findLowerBound
void __thiscall Tree::findLowerBound(uint *keyPtr, Pair *out)
// Function at 0x005df150: Binary search tree lower bound search.
// Returns the node with the greatest key <= *keyPtr. If not found, returns root.
// Tree root pointer stored at this+0x1c. Node structure:
//   +0x00: right child (Node*)
//   +0x04: unknown (maybe parent or sibling)
//   +0x08: left child (Node*)
//   +0x0C: key (uint32_t)
//   +0x15: leaf flag (0 = internal node, non-zero = leaf)
{
    Node *current = *(Node **)((char *)this + 0x1c); // root
    Node *parent = current;

    // Check if root's right child is internal; if not, skip traversal
    if (*(char *)((int)current->field_0x04 + 0x15) == '\0')
    {
        Node *node = current;
        do
        {
            if (node->key < *keyPtr)
            {
                // Go right
                parent = node;
                node = node->right;
            }
            else
            {
                // Go left
                parent = node;
                node = node->left;
            }
        } while (*(char *)((int)node + 0x15) == '\0'); // stop at leaf
        // After loop, 'node' is a leaf, 'parent' is its last internal ancestor
    }

    // Determine result: if parent is valid and its key <= target, use parent; else use root
    Node *result;
    if (parent != current && parent->key <= *keyPtr)
        result = parent;
    else
        result = current;

    // Write output pair: [0] = this, [1] = result node
    out->thisPtr = this;
    out->nodePtr = result;
}