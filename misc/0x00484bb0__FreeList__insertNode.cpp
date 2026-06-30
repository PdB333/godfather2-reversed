// FUNC_NAME: FreeList::insertNode
void __thiscall FreeList::insertNode(int thisPointer, int listPointer)
{
    // Dereference the node pointer stored at this+0x08 (the object's embedded list node)
    int *node = *(int **)(thisPointer + 8);
    // Update this object's node pointer to point to the next node in the list
    *(int *)(thisPointer + 8) = *node;

    // If the node's flag at offset 0x15 is zero, set its previous pointer to this object
    if (*(char *)(*node + 0x15) == '\0') {
        *(int *)(*node + 4) = thisPointer;
    }

    // Set the node's next pointer to the object's previous (or tail?) pointer at this+4
    node[1] = *(int *)(thisPointer + 4);

    // Check if this object is equal to the tail of the list (listPointer+4 points to a tail pointer)
    if (thisPointer == *(int *)(*(int *)(listPointer + 4) + 4)) {
        // Update the tail to the node
        *(int **)(*(int *)(listPointer + 4) + 4) = node;
        *node = thisPointer;
        *(int **)(thisPointer + 4) = node;
        return;
    }

    int *prevNode = *(int **)(thisPointer + 4);
    // Check if this object is the head of the list (prevNode's first field)
    if (thisPointer == *prevNode) {
        // Update the head
        *prevNode = (int)node;
        *node = thisPointer;
        *(int **)(thisPointer + 4) = node;
        return;
    }

    // General case: insert node between prevNode and this object
    prevNode[2] = (int)node;
    *node = thisPointer;
    *(int **)(thisPointer + 4) = node;
    return;
}