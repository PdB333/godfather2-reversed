// FUNC_NAME: SpatialTree::insert
void __cdecl SpatialTree::insert(int unused, SpatialTreeNode* rootNode, int x, int y, int depth, SpatialTreeElement* element)
{
    // Node layout (int*):
    // +0x00: count (number of elements in this node)
    // +0x04: subCount (number of subnodes/elements inserted)
    // +0x08..+0x408: children[256] (pointers to child nodes or elements at leaf)
    // Element layout:
    // +0x18: nextElement (or sibling pointer)
    // +0x1c: parentNode (pointer to the leaf node containing this element)

    rootNode->subCount++; // +0x04

    int shift = depth * 4; // number of bits to extract
    int ix = (x >> (shift & 0x1f)) & 0xF; // 4-bit x index
    int iy = (y >> (shift & 0x1f)) & 0xF; // 4-bit y index
    int slot = ix * 16 + iy; // 0..255

    SpatialTreeNode* child = (SpatialTreeNode*)rootNode->children[slot];
    SpatialTreeNode* currentNode = rootNode;

    while (depth != 0)
    {
        // Descend to the next level
        if (child == nullptr)
        {
            child = (SpatialTreeNode*)allocateTreeNode(); // FUN_00415c70
            currentNode->count++;
            currentNode->children[slot] = (int*)child;
        }

        // Remove the higher bits from coordinates
        int highMask = (ix << shift);
        int highMaskY = (iy << shift);
        x -= highMask;
        y -= highMaskY;

        shift -= 4;
        child->subCount++; // new node's counter
        depth--;

        // Calculate next level indices
        ix = (x >> (shift & 0x1f)) & 0xF;
        iy = (y >> (shift & 0x1f)) & 0xF;
        slot = ix * 16 + iy;

        currentNode = child;
        child = (SpatialTreeNode*)child->children[slot];
    }

    // Insert into leaf node
    rootNode->count++; // actually param_2 points to the leaf node here, increment its count

    // Set element back-pointers
    element->parentNode = rootNode; // +0x1c
    if (rootNode != nullptr)
    {
        rootNode->children[4] = (int*)element; // piVar2[6] -> offset 0x18 (fixed slot for first element)
    }
    element->nextElement = nullptr; // +0x18 = 0

    // Store element in the appropriate leaf slot
    rootNode->children[slot] = (int*)element;
}