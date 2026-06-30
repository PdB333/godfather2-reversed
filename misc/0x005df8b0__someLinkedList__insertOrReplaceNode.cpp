// FUNC_NAME: someLinkedList::insertOrReplaceNode
void __thiscall someLinkedList::insertOrReplaceNode(int param_1, int param_2)
{
    int *currentNode;
    int *nextNode;
    
    // Get the next node from the list head (offset +0x8)
    currentNode = *(int **)(param_1 + 8);
    *(int *)(param_1 + 8) = *currentNode;
    
    // If the node's flag at offset +0x15 is zero, update its previous pointer
    if (*(char *)(*currentNode + 0x15) == '\0') {
        *(int *)(*currentNode + 4) = param_1;
    }
    
    currentNode[1] = *(int *)(param_1 + 4);
    
    // Check if the current node is the head of the list (param_2 + 0x1c points to list head)
    if (param_1 == *(int *)(*(int *)(param_2 + 0x1c) + 4)) {
        // Replace the head node
        *(int **)(*(int *)(param_2 + 0x1c) + 4) = currentNode;
        *currentNode = param_1;
        *(int **)(param_1 + 4) = currentNode;
        return;
    }
    
    // Update the next pointer of the previous node
    nextNode = *(int **)(param_1 + 4);
    if (param_1 == *nextNode) {
        *nextNode = (int)currentNode;
        *currentNode = param_1;
        *(int **)(param_1 + 4) = currentNode;
        return;
    }
    
    // Update the previous node's forward link
    nextNode[2] = (int)currentNode;
    *currentNode = param_1;
    *(int **)(param_1 + 4) = currentNode;
    return;
}