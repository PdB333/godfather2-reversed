// FUNC_NAME: TreeMap::findLessEqual
// Address: 0x005def60
// Role: Binary search tree lookup: finds node with greatest key <= given key.
// Class likely part of EA EARS engine's custom container.
// Structure offsets are relative to 'this' (passed in ESI).
// Tree nodes have: left child at +0x0, right child at +0x8, key at +0xC, leaf flag at +0x15 (0=internal, 1=leaf).
// The root pointer is stored at this+0x1c, but the actual root is accessed via root_ptr[1] (offset 0x4) when the sentinel's leaf flag is 0.
// Output is written to a Result structure pointed by in_EAX (first field = this, second = found node).

void TreeMap::findLessEqual(uint key)
{
    // Fetch the sentinel node pointer from this+0x1c
    TreeNode* sentinel = *(TreeNode**)(this + 0x1c);
    TreeNode* best = sentinel;  // candidate for result

    // If the sentinel's child (actual root) is not a leaf, traverse
    if (*(char*)((int)sentinel->child + 0x15) == '\0') // child at +0x4
    {
        TreeNode* current = (TreeNode*)sentinel->child;
        do
        {
            // Compare keys: smaller key go right (+0x8), larger/equal go left (+0x0)
            if (current->key < key)
            {
                current = (TreeNode*)current->right;  // +0x8
            }
            else
            {
                best = current;
                current = (TreeNode*)current->left;   // +0x0
            }
        } while (*(char*)((int)current + 0x15) == '\0'); // loop while not leaf
    }

    // Now check if the best candidate (non-sentinel) has key <= given key
    if (best != sentinel && best->key <= key)
    {
        *outputPtr = this;
        *(TreeNode**)(outputPtr + 4) = best;
    }
    else
    {
        *outputPtr = this;
        *(TreeNode**)(outputPtr + 4) = sentinel;
    }
}