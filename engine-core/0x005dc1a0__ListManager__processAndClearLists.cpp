// FUNC_NAME: ListManager::processAndClearLists
int __thiscall ListManager::processAndClearLists(void) {
    int listPtr;
    int *firstNode;
    int *nodeHead;
    int nodeData;
    int result = 0;

    // Check if both list pointers are valid (offset +0x08 and +0x0C)
    if ((this->listA != 0) && (this->listB != 0)) {
        // Iterate while there is a next node in listA (offset +0x20 from listA)
        listPtr = *(int *)(this->listA + 0x20);
        while (listPtr != 0) {
            listPtr = this->listA;
            // Get head of node list (offset +0x1C from listA)
            nodeHead = *(int **)(listPtr + 0x1C);
            firstNode = (int *)*nodeHead;
            if (firstNode == nodeHead) {
                // Empty list – call assertion/error handler
                assertionFailure(); // FUN_00b97aea
            }
            nodeData = firstNode[4]; // offset +0x10? Actually +4 ints -> +16 bytes
            // Process the node (call FUN_005dec30 with listA, buffer, listPtr, node)
            processNode(this->listA, localBuffer, listPtr, firstNode);
            if ((this->callback != 0) && (nodeData != 0)) {
                preCleanupCallback();  // FUN_005dcdc0
                deallocateData(nodeData); // FUN_009c8eb0
            }
            // Get next list pointer for the loop condition
            listPtr = *(int *)(this->listA + 0x20);
        }
        // Free listA
        listPtr = this->listA;
        if (listPtr != 0) {
            freeListNodeList();  // FUN_005deac0
            deallocate(listPtr); // FUN_009c8eb0
        }
        // Free listB
        listPtr = this->listB;
        this->listA = 0;
        if (listPtr != 0) {
            freeOtherList();  // FUN_005df0e0
            deallocate(listPtr); // FUN_009c8eb0
        }
        this->listB = 0;
        // Cleanup callback object (offset +0x04)
        if (this->callback != 0) {
            (*(void (__thiscall **)(int))(*(int *)this->callback + 0xC))(this->callback);
            this->callback = 0;
        }
        result = 1;
    }
    return result;
}