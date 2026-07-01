// FUNC_NAME: LinkedList::swapNodeWithNext
void __thiscall LinkedList::swapNodeWithNext(int thisPtr, int nodePtr)
{
    int *nextNode;            // Node immediately after nodePtr
    int *prevNode;            // Node immediately before nodePtr

    // nextNode = nodePtr->next (offset +0x8)
    nextNode = *(int **)(nodePtr + 8);
    // nodePtr->next = nextNode->next (i.e., skip the next node)
    *(int *)(nodePtr + 8) = *nextNode;

    // If the next node's flag at offset +0x25 is zero, update its prev pointer to nodePtr
    if (*(char *)(*nextNode + 0x25) == '\0') {
        *(int *)(*nextNode + 4) = nodePtr;
    }

    // Update nextNode->prev to nodePtr->prev (offset +0x4)
    nextNode[1] = *(int *)(nodePtr + 4);

    // Check if nodePtr is the tail of the list (last node in the sentinel-based list)
    if (nodePtr == *(int *)(*(int *)(thisPtr + 4) + 4)) {
        // Adjust tail pointer: list tail's next becomes nextNode
        *(int **)(*(int *)(thisPtr + 4) + 4) = nextNode;
        // nextNode->next = nodePtr (swap back? actually sets nextNode's first field to nodePtr)
        *nextNode = nodePtr;
        // nodePtr->prev = nextNode
        *(int **)(nodePtr + 4) = nextNode;
        return;
    }

    // Otherwise, get previous node
    prevNode = *(int **)(nodePtr + 4);

    // If nodePtr is the head of the list (nodePtr equals prevNode->next)
    if (nodePtr == *prevNode) {
        // Adjust head's next: prevNode->next = nextNode
        *prevNode = (int)nextNode;
        // nextNode->next = nodePtr
        *nextNode = nodePtr;
        // nodePtr->prev = nextNode
        *(int **)(nodePtr + 4) = nextNode;
        return;
    }

    // General case: adjust the node two steps before (prevNode's forward pointer at +8)
    prevNode[2] = (int)nextNode;
    *nextNode = nodePtr;
    *(int **)(nodePtr + 4) = nextNode;
    return;
}