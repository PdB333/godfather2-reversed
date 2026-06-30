//FUNC_NAME: NodeList::insertNodeAfter
void __thiscall NodeList::insertNodeAfter(int *thisPtr, int *nodeToInsertAfter)
{
    int *newNode;
    int currentSize;
    int capacity;

    currentSize = thisPtr[1]; // +0x04: current number of nodes
    capacity = thisPtr[2];    // +0x08: capacity of the array

    if (currentSize == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity = capacity * 2;
        }
        // Grow the array to new capacity (calls realloc-like function)
        FUN_006bc970(capacity);
    }

    // Calculate pointer to the new node slot at the end of the array
    newNode = (int *)(*thisPtr + currentSize * 8); // each node is 8 bytes
    thisPtr[1] = currentSize + 1; // increment size

    if (newNode != (int *)0x0) {
        int nodeValue = *nodeToInsertAfter; // value to store in the new node
        *newNode = nodeValue;               // store data (first 4 bytes)
        newNode[1] = 0;                     // initialize next pointer to null

        if (nodeValue != 0) {
            // Insert newNode after the node pointed to by nodeValue
            // nodeValue is treated as a node pointer; its +0x04 is the next pointer
            newNode[1] = *(int *)(nodeValue + 4); // copy the old next pointer
            *(int **)(nodeValue + 4) = newNode;   // update the previous node's next to point to newNode
        }
    }
    return;
}