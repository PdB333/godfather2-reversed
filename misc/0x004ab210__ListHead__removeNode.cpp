// FUNC_NAME: ListHead::removeNode
void __thiscall ListHead::removeNode(void* thisPtr) {
    // thisPtr+0x10: pointer to first node (or node list head's 'next')
    // thisPtr+0x14: pointer to last node (or node list head's 'prev')
    // Nodes have: +0x0: next, +0x4: prev
    int firstNode = *(int*)((char*)thisPtr + 0x10);
    if (firstNode != 0) {
        int prevOfFirst = *(int*)(firstNode + 4);
        if (prevOfFirst == (int)((char*)thisPtr + 0x10)) {
            // Only one node: set its prev to the tail pointer
            *(int*)(firstNode + 4) = *(int*)((char*)thisPtr + 0x14);
        } else {
            // Traverse to find the node previous to the first node in the circular list
            int currentNode = firstNode;
            int prevNode = prevOfFirst;
            while (currentNode != (int)((char*)thisPtr + 0x10)) {
                prevNode = *(int*)(prevNode + 4);
                currentNode = *(int*)(prevNode + 4);
            }
            *(int*)(prevNode + 4) = *(int*)((char*)thisPtr + 0x14);
        }
    }
}