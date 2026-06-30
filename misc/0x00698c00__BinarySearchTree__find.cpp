// FUNC_NAME: BinarySearchTree::find
// Address: 0x00698c00
// Binary search tree traversal. Nodes have left child at offset 0, right child at offset 4.
// Key comparison via FUN_004d4b20 (takes single parameter, likely the search key; actual node key stored internally?).
void __thiscall BinarySearchTree::find(int this, int* outNodePtr, int key)
{
    // +0x4: sentinel/header node (used as end marker)
    int* sentinel = (int*)(this + 4);

    // +0xC: root pointer
    int* current = *(int**)(this + 0xC);

    // Track the last node where we moved right (i.e., comparison >= 0)
    int* lastRight = sentinel;

    // Traverse the tree
    while (current != 0)
    {
        int cmp = FUN_004d4b20(key); // result: <0 go left, >=0 go right
        if (cmp < 0)
        {
            // Go left: left child at offset 0
            current = (int*)*current;
        }
        else
        {
            // Go right: right child at offset 4
            lastRight = current;
            current = (int*)current[1];
        }
    }

    // After traversal, check the last candidate node
    if (lastRight != sentinel)
    {
        // Re-compare with candidate: note offset +4 may be key or right child pointer.
        int cmp2 = FUN_004d4b20((int)(lastRight + 4));
        if (cmp2 >= 0)
        {
            *outNodePtr = lastRight;
            return;
        }
    }

    // No suitable node found; return the sentinel
    *outNodePtr = sentinel;
}