// FUNC_NAME: QueueProcessor::processAndClearQueues
// Function at 0x005dc1a0 - Clears and processes two internal queues (linked lists) and releases associated resources.
// Likely a cleanup method called during shutdown or flush.

int __thiscall QueueProcessor::processAndClearQueues(void) {
    int *currentNode;          // iVar1 - current node from first queue list
    int *listHead;             // piVar2 - pointer to list head embedded in container
    int *listNode;             // piVar3 - first list node
    int nodeData;              // iVar4 - data extracted from node (offset +0x10? Actually node[4])
    int retVal = 0;
    char tempBuf[12];          // local_10 - buffer passed to processing function

    // Check if both queue containers are allocated (offsets +0x08 and +0x0C)
    if (*(int *)(this + 8) != 0 && *(int *)(this + 0x0C) != 0) {
        currentNode = *(int **)(*(int *)(this + 8) + 0x20); // get head of linked list from first queue container (offset +0x20)
        while (currentNode != 0) {
            // Refresh pointer to container (might have been updated)
            currentNode = *(int **)(this + 8); 
            listHead = *(int **)(currentNode + 0x1C); // get list head pointer from container (offset +0x1C)
            listNode = (int *)*listHead;              // dereference to get first list node
            // Check for empty list (sentinel self-loop)
            if (listNode == listHead) {
                FUN_00b97aea(); // likely assertion failure (list corruption)
            }
            nodeData = listNode[4]; // retrieve data at node + 0x10 (since int*)
            // Process the node: pass container (+0x08), temp buffer, container pointer, and node pointer
            FUN_005dec30(*(int *)(this + 8), tempBuf, (int)currentNode, listNode);
            // If there is a callback object (+0x04) and node data is non-null, call additional processing and release node data
            if (*(int *)(this + 4) != 0 && nodeData != 0) {
                FUN_005dcdc0(); // probably performs some action on callback object
                FUN_009c8eb0(nodeData); // free/release the node data
            }
            // Get next node from container's linked list (offset +0x20)
            currentNode = *(int **)(*(int *)(this + 8) + 0x20);
        }
        // After processing all nodes, release the first container itself
        currentNode = *(int **)(this + 8);
        if (currentNode != 0) {
            FUN_005deac0();    // likely destructor or pre-release for first container
            FUN_009c8eb0(currentNode); // free memory
        }
        *(int *)(this + 8) = 0; // clear pointer

        // Release the second container
        currentNode = *(int **)(this + 0x0C);
        if (currentNode != 0) {
            FUN_005df0e0();    // likely destructor or pre-release for second container
            FUN_009c8eb0(currentNode); // free memory
        }
        *(int *)(this + 0x0C) = 0; // clear pointer

        // Release the callback object if present (+0x04)
        if (*(int **)(this + 4) != 0) {
            // Call virtual function at offset +0x0C (likely release/destructor)
            (*(code (__thiscall **)(int))(*(int *)(this + 4) + 0x0C))(*(int *)(this + 4));
            *(int *)(this + 4) = 0; // clear pointer
        }
        retVal = 1; // success
    }
    return retVal;
}