// FUNC_NAME: BinaryTree::insertOrFind
void __thiscall BinaryTree::insertOrFind(int thisPtr, int *outEntry, int key)
{
    char nodeFlag;
    int *currentNode;
    int *prevNode;
    int comparisonResult;
    int *newNode;
    int *childPtr;
    bool goRight;

    currentNode = *(int ***)(thisPtr + 4)[1]; // +0x04: root pointer? Actually [1] means second element?
    goRight = true;
    nodeFlag = *(char *)((int)currentNode + 0x25); // +0x25: node flag (e.g., isLeaf or color)
    prevNode = *(int **)(thisPtr + 4);

    while (nodeFlag == '\0') { // loop until we find a marked node (sentinel/leaf)
        comparisonResult = FUN_004d4b20(currentNode + 3); // +0x0C: node's key (offset 12)
        goRight = comparisonResult < 0;
        if (goRight) {
            childPtr = (int *)*currentNode; // offset +0x00: left child
        } else {
            childPtr = (int *)currentNode[2]; // offset +0x08: right child
        }
        prevNode = currentNode;
        currentNode = childPtr;
        nodeFlag = *(char *)((int)childPtr + 0x25);
    }

    // Now we have reached a leaf/marked node; prevNode is parent
    // outEntry will store the result
    int treePtr = thisPtr;
    int *leafNode = prevNode;

    if (goRight) {
        if (prevNode == *(int **)*thisPtr) { // root sentinel check?
            newNode = (int *)FUN_00695f00(&treePtr, 1, prevNode, key); // allocate new node
            int newKey = *newNode;
            outEntry[1] = newNode[1];
            *(char *)(outEntry + 2) = 1; // flag = 1 (inserted)
            *outEntry = newKey;
            return;
        }
        FUN_00694060(); // error or handle duplicate
    }

    currentNode = leafNode;
    comparisonResult = FUN_004d4b20(key); // compare key with something? Actually param is key
    if (comparisonResult >= 0) {
        outEntry[1] = (int)currentNode;
        *(char *)(outEntry + 2) = 0; // flag = 0 (found existing)
        *outEntry = treePtr;
        return;
    }

    // need to insert
    newNode = (int *)FUN_00695f00(&treePtr, goRight, prevNode, key);
    int newKey = *newNode;
    outEntry[1] = newNode[1];
    *(char *)(outEntry + 2) = 1; // inserted
    *outEntry = newKey;
    return;
}