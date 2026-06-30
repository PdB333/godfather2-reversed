// FUNC_NAME: Tree::insert
void __thiscall Tree::insert(void* thisTree, int* outputIterator, char insertDirection)
{
    // +0x20: tree size (unsigned int)
    uint treeSize = *(uint*)((char*)thisTree + 0x20);
    if (treeSize > 0x1ffffffd)
    {
        // Exception: map/set<T> too long
        // (standard exception for exceeding max size)
        // ... exception handling omitted ...
    }

    // Allocate a new node (FUN_005e0110 likely allocates a node)
    int* newNode = (int*)FUN_005e0110(*(undefined4*)((char*)thisTree + 0x1c), /*some arg*/);
    // +0x1c: pointer to tree header (sentinel node or similar)

    // Increment size
    (*(uint*)((char*)thisTree + 0x20))++;

    // Get tree header pointer (at thisTree+0x1c points to a structure with offsets 0, 4, 8)
    int* header = *(int**)((char*)thisTree + 0x1c); // header node with leftmost/rightmost/root

    // Insert the new node into the tree
    // header[0] = leftmost, header[1] = rightmost, header[2] = root sentinel?
    if (/*some condition*/) // unaff_EDI is some node (maybe the hint)
    {
        header[1] = newNode;
        header[0] = newNode;
        *(int**)(header + 2) = newNode; // header + 8 = root pointer
    }
    else if (insertDirection == '\0')
    {
        // insert before the hint node
        // ... pointer manipulation ...
    }
    else
    {
        // insert after the hint node
        // ... pointer manipulation ...
    }

    // Red-black tree rebalancing
    char color;
    int* current = newNode;
    while (true)
    {
        color = *(char*)(current[1] + 0x14); // parent's color (0x14 from node? or from parent pointer)
        if (color != '\0')
            break; // parent is black, tree ok

        // parent color is red -> need rotations and recoloring
        int* parent = (int*)current[1]; // +0x04: parent pointer
        int* grandparent = (int*)parent[1]; // grandparent

        if (parent == (int*)grandparent[2]) // parent is right child of grandparent?
        {
            // ... rotation and recoloring logic ...
        }
        else
        {
            // parent is left child
            // ... similar logic ...
        }
        current = parent; // move up
    }

    // Set root node to black
    *(char*)(*(int*)(*(int*)((char*)thisTree + 0x1c) + 4) + 0x14) = 1; // root's parent? Actually root's color set to black

    // Set output iterator
    outputIterator[1] = (int)newNode;
    *outputIterator = (int)thisTree;
    return;
}