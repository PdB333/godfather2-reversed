// FUNC_NAME: someTreeIterator::advanceToNextActiveNode
void someTreeIterator::advanceToNextActiveNode()
{
    char cVar1;
    int *currentNode;
    int iVar3;
    int iVar4;

    if (rootNode == 0) {
        FUN_00b97aea(); // likely return/throw on invalid
    }
    currentNode = (int *)currentNodePtr;
    if (*(char *)((int)currentNode + 0x15) == '\0') {
        // Node is inactive, walk up/down tree to find next active
        iVar3 = *currentNode; // +0x00: parent node pointer
        if (*(char *)(iVar3 + 0x15) == '\0') {
            // Parent is also inactive, go to sibling
            cVar1 = *(char *)(*(int *)(iVar3 + 8) + 0x15); // +0x08: next sibling pointer
            iVar4 = *(int *)(iVar3 + 8);
            while (cVar1 == '\0') {
                cVar1 = *(char *)(*(int *)(iVar4 + 8) + 0x15);
                iVar3 = iVar4;
                iVar4 = *(int *)(iVar4 + 8);
            }
            currentNodePtr = iVar3;
            return;
        }
        // Parent is active, go to its first child
        currentNode = (int *)currentNode[1]; // +0x04: child pointer
        cVar1 = *(char *)((int)currentNode + 0x15);
        while ((cVar1 == '\0' && (currentNodePtr == *currentNode))) {
            currentNodePtr = (int)currentNode;
            currentNode = (int *)currentNode[1]; // +0x04: child pointer
            cVar1 = *(char *)((int)currentNode + 0x15);
        }
        if (*(char *)(currentNodePtr + 0x15) != '\0') {
            FUN_00b97aea(); // unexpected active node found
            return;
        }
        currentNodePtr = (int)currentNode;
    }
    else {
        // Current node is active, advance to its first child
        iVar3 = currentNode[2]; // +0x08: first child pointer
        currentNodePtr = iVar3;
        if (*(char *)(iVar3 + 0x15) != '\0') {
            FUN_00b97aea(); // unexpected active node found
            return;
        }
    }
    return;
}