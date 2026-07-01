// FUNC_NAME: CircularNodeList::findMatchingEdgeIndex
// Function address: 0x0082c4d0
// Role: Searches a circular list of nodes for a pair of consecutive nodes that satisfy a connection condition.
// The list is stored as an array of pointers to node structures. Each node has a field at offset +0x4 used for comparison.
// The comparison function (FUN_00821840) checks if two nodes are connected given a context parameter (param_2).
// Returns the index of the first node in the matching pair, or 0xFFFFFFFF if not found.

uint __thiscall CircularNodeList::findMatchingEdgeIndex(int thisPtr, uint contextParam)
{
    char comparisonResult;
    int nextIndex;
    uint currentIndex;
    uint loopIndex;

    int count = *(int *)(thisPtr + 0xC); // +0xC: number of nodes in the list
    if (count == 0) {
        return 0xFFFFFFFF;
    }
    if (count == 1) {
        return 0;
    }

    currentIndex = *(uint *)(thisPtr + 0x4); // +0x4: current index (starting point)
    // Compute the next index circularly
    if (currentIndex < (uint)(count - 1)) {
        nextIndex = currentIndex + 1;
    } else {
        nextIndex = 0;
    }

    // Compare the node at currentIndex with the node at nextIndex
    comparisonResult = FUN_00821840(
        contextParam,
        *(int *)(*(int *)(thisPtr + 0x8) + currentIndex * 4) + 4, // nodeA->fieldAtOffset4
        *(int *)(*(int *)(thisPtr + 0x8) + nextIndex * 4) + 4    // nodeB->fieldAtOffset4
    );
    if (comparisonResult != '\0') {
        return *(uint *)(thisPtr + 0x4); // Return current index
    }

    // Iterate through all nodes to find a matching pair
    uint nodeCount = *(uint *)(thisPtr + 0xC); // +0xC: count
    loopIndex = 0;
    if (nodeCount != 0) {
        do {
            if (loopIndex < nodeCount - 1) {
                nextIndex = loopIndex + 1;
            } else {
                nextIndex = 0;
            }
            comparisonResult = FUN_00821840(
                contextParam,
                *(int *)(*(int *)(thisPtr + 0x8) + loopIndex * 4) + 4,
                *(int *)(*(int *)(thisPtr + 0x8) + nextIndex * 4) + 4
            );
            if (comparisonResult != '\0') {
                return loopIndex;
            }
            nodeCount = *(uint *)(thisPtr + 0xC);
            loopIndex = loopIndex + 1;
        } while (loopIndex < nodeCount);
    }
    return 0xFFFFFFFF;
}