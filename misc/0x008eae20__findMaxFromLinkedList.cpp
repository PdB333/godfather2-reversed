// FUNC_NAME: findMaxFromLinkedList
int findMaxFromLinkedList(undefined4** listHeadPtr)
{
    // Traverse a linked list where each node's first field is a pointer to the next node.
    // Call getNodeValue on each node and return the maximum value found.
    // Returns -999999 if the list is empty.
    undefined4* currentNode = *listHeadPtr;
    int maxValue = -999999;
    while (currentNode != (undefined4*)0x0) {
        int value = FUN_008e9ce0(currentNode); // getNodeValue(node)
        currentNode = (undefined4*)*currentNode; // advance to next node via first field (next pointer)
        if (maxValue < value) {
            maxValue = value;
        }
    }
    return maxValue;
}