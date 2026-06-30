// FUNC_NAME: LinkedList::moveNodeBefore
// Function at 0x00623d50: Moves a node (pointed by this->+8) to the position immediately before this node in a doubly linked list.
// The list uses a sentinel head node at listHead+0x1c (offset 0x1c from param_2).
// Node structure:
//   +0x00: prev (pointer to previous node)
//   +0x04: next (pointer to next node)
//   +0x08: some pointer (used to track a node to move, e.g., a "current" or "pending" node)
//   +0x15: flag byte (if zero, the moved node's next is set to this)

void __thiscall LinkedList::moveNodeBefore(int thisNode, int listHead)
{
    int *movedNode;       // piVar1 - the node to be moved (pointed by thisNode+8)
    int *nextNode;        // piVar2 - the node after thisNode

    // Get the node to move from thisNode's +8 field
    movedNode = *(int **)(thisNode + 8);
    // Update thisNode's +8 to skip over movedNode (effectively removing movedNode from its current position)
    *(int *)(thisNode + 8) = *movedNode;

    // If the flag at movedNode+0x15 is zero, set movedNode's next to thisNode
    if (*(char *)(*movedNode + 0x15) == '\0') {
        *(int *)(*movedNode + 4) = thisNode;
    }

    // Set movedNode's previous to thisNode's previous
    movedNode[1] = *(int *)(thisNode + 4);

    // Check if thisNode is the first real node after the sentinel head (listHead+0x1c)
    if (thisNode == *(int *)(*(int *)(listHead + 0x1c) + 4)) {
        // Update sentinel's next to movedNode (movedNode becomes new first node)
        *(int **)(*(int *)(listHead + 0x1c) + 4) = movedNode;
        *movedNode = thisNode;          // movedNode's prev = thisNode
        *(int **)(thisNode + 4) = movedNode; // thisNode's next = movedNode
        return;
    }

    // Get the node after thisNode
    nextNode = *(int **)(thisNode + 4);

    // If thisNode is the previous of its next node (standard doubly linked list invariant)
    if (thisNode == *nextNode) {
        // Update nextNode's prev to movedNode
        *nextNode = (int)movedNode;
        *movedNode = thisNode;          // movedNode's prev = thisNode
        *(int **)(thisNode + 4) = movedNode; // thisNode's next = movedNode
        return;
    }

    // Fallback (should not occur in a consistent list): update nextNode's +8 field
    nextNode[2] = (int)movedNode;
    *movedNode = thisNode;
    *(int **)(thisNode + 4) = movedNode;
}