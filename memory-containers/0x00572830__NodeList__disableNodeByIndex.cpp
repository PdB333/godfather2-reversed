// FUNC_NAME: NodeList::disableNodeByIndex
// Function address: 0x00572830
// This function traverses a linked list of nodes (each node has a 'next' pointer at offset 0x124) starting from head at this+0x124.
// It advances 'index' steps, then clears bit 28 (0x10000000) at node+0x10 (likely an active flag).
// Returns 1 on success, 0 if node is null or index is negative.

uint8 __fastcall NodeList::disableNodeByIndex(void* pThis, int index) {
    uint8 result = 0;

    if (pThis == 0 || index < 0) {
        return 0;
    }

    int* currentNode = *(int**)((int)pThis + 0x124); // +0x124: head of linked list
    int i = 0;

    if (index > 0) {
        do {
            currentNode = *(int**)((int)currentNode + 0x124); // +0x124: next pointer
            if (currentNode == 0) {
                return 0;
            }
            i++;
        } while (i < index);
    }

    if (currentNode != 0) {
        *(unsigned int*)((int)currentNode + 0x10) &= 0xefffffff; // +0x10: flags, clears bit 28
        result = 1;
    }

    return result;
}