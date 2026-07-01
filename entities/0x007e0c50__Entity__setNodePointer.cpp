//FUNC_NAME: Entity::setNodePointer
void __thiscall Entity::setNodePointer(int thisPtr, int nodePtr)
{
    int *nodeSlot = (int *)(thisPtr + 0x12C); // +0x12C: pointer to a node (e.g., child list head)
    int adjustedNode;

    if (nodePtr == 0) {
        adjustedNode = 0;
    } else {
        adjustedNode = nodePtr + 0x48; // offset to a field within the node structure (e.g., next pointer)
    }

    if (*nodeSlot != adjustedNode) {
        if (*nodeSlot != 0) {
            FUN_004daf90(nodeSlot); // remove old node from list
        }
        *nodeSlot = adjustedNode;
        if (adjustedNode != 0) {
            *(int *)(thisPtr + 0x130) = *(int *)(adjustedNode + 4); // copy node's prev pointer to this+0x130
            *(int **)(adjustedNode + 4) = nodeSlot; // set node's prev pointer to point to this's nodeSlot
        }
    }
}