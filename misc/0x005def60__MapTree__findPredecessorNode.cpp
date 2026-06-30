// FUNC_NAME: MapTree::findPredecessorNode

// This function finds the node with the largest key <= given key in a binary search tree
// (likely a red-black tree). It is part of the EA EARS engine's custom map implementation.
// The tree uses a sentinel node (leaf flag at offset 0x15 = 0 for internal, non-zero for leaf).
// 
// Node layout (byte offsets from node pointer):
//   0x00: left child (MapNode*)
//   0x04: right child (MapNode*)
//   0x08: parent (MapNode*, inferred, not directly used here)
//   0x0C: key (uint32)
//   0x15: leaf flag (char, 0 = internal node, != 0 = sentinel)
//
// Class layout (byte offset from this):
//   0x1C: root pointer (pointer to sentinel node)
//
// Original function (at 0x005def60) writes two outputs to a pointer stored in EAX:
//   out[0] = this (the tree)
//   out[1] = result node (found node or sentinel root)
// For reconstruction, we return the node pointer directly. The caller would also have
// access to 'this' implicitly.

__thiscall MapNode* MapTree::findPredecessorNode(uint key) const
{
    // Retrieve sentinel root from this+0x1C
    MapNode* sentinel = *(MapNode**)((char*)this + 0x1C);
    // Start traversal from sentinel's right child (actual root of the tree)
    MapNode* current = sentinel->right;        // Root node (may be sentinel itself if empty)
    MapNode* candidate = sentinel;            // Best node found so far

    // Check if tree is non-empty (sentinel's right child is not a leaf)
    if (current->leafFlag == 0)  // internal node
    {
        do
        {
            if (current->key < key)
            {
                // Key is larger -> go right
                current = current->right;
            }
            else
            {
                // Key <= current->key -> go left and remember this node as candidate
                current = current->left;
                candidate = current;            // Update candidate (last node where we went left)
            }
        } while (current->leafFlag == 0);      // Continue until we hit a leaf sentinel
    }

    // After traversal, candidate holds the deepest node where we went left (or sentinel if never)
    if (candidate != sentinel && candidate->key <= key)
    {
        return candidate;                       // Found predecessor
    }
    else
    {
        return sentinel;                        // No predecessor (return sentinel)
    }
}