// FUNC_NAME: SpatialTreeNode::traverseGetChild
int* __cdecl SpatialTreeNode::traverseGetChild(int* pOutChild,
                                               SpatialTreeNode* pNode,
                                               int coordX,
                                               int coordY,
                                               int depthLevel)
{
    // Shifts coordinates by depthLevel*4 bits to extract the quadrant index at this level.
    unsigned int shiftAmount = depthLevel * 4;
    int quadrantX = coordX >> (shiftAmount & 31);
    int quadrantY = coordY >> (shiftAmount & 31);

    // Children are stored in a 16x16 grid (256 children) starting at offset +0x8 from node.
    // Index = quadrantX * 16 + quadrantY  (since each child is 4 bytes, pointer sized).
    int childIndex = quadrantX * 16 + quadrantY;
    int* childrenArray = reinterpret_cast<int*>(reinterpret_cast<char*>(pNode) + 8);
    SpatialTreeNode* pChild = reinterpret_cast<SpatialTreeNode*>(childrenArray[childIndex]);

    if (pChild != nullptr && depthLevel != 0)
    {
        // Recurse into child with refined coordinates (remove the bits we just used).
        int newX = coordX - (quadrantX << (shiftAmount & 31));
        int newY = coordY - (quadrantY << (shiftAmount & 31));
        return traverseGetChild(pOutChild, pChild, newX, newY, depthLevel - 1);
    }

    // Either reached leaf (depthLevel == 0) or child is null.
    *pOutChild = reinterpret_cast<int>(pChild);
    return pOutChild;
}