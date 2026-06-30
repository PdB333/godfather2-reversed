// FUNC_NAME: PriorityQueue::popNextItem
int __fastcall PriorityQueue::popNextItem(int *state) // state is parameter 2 (edx), ecx unused
{
    // state structure:
    // +0x00: matchKey (int) - key to match for continuing iteration
    // +0x04: currentA (int*) - pointer to current slot in first list (array of node pointers)
    // +0x08: currentB (int*) - pointer to current slot in second list
    // +0x0C: end (int*) - end of the combined arrays
    int* currentA = (int*)state[1];
    int* currentB = (int*)state[2];
    int* end = (int*)state[3];

    int nextKey;

    // If first list is empty, go to pop from second list
    if (currentA == nullptr) {
        goto popFromB;
    }

    // If second list is not empty, compare priorities
    if (currentB != nullptr) {
        int* nodeA = (int*)*currentA; // node pointer from list A
        int nodeAKey;
        // Check flag at offset 0x0B bit 0x20 and size field at offset 0
        if ((*(unsigned char*)(nodeA + 0x0B) & 0x20) == 0 || *nodeA < 2) {
            nodeAKey = *nodeA; // use first field
        } else {
            nodeAKey = nodeA[1]; // use second field
        }

        int* nodeB = (int*)*currentB;
        int nodeBKey;
        if ((*(unsigned char*)(nodeB + 0x0B) & 0x20) == 0 || *nodeB < 4) {
            nodeBKey = *nodeB;
        } else {
            nodeBKey = nodeB[5]; // use sixth field
        }

        // If second list has smaller priority, pop from second list
        if (nodeBKey < nodeAKey) {
            goto popFromB;
        }
    }

    // Pop from first list (list A)
    nextKey = *currentA; // store the node pointer (cast to int?)
    currentA++; // advance pointer
    state[1] = (int)currentA; // update currentA

    // If we haven't reached end, check if the next node's key matches matchKey
    if (currentA < end) {
        int* nextNode = (int*)*currentA;
        int nextNodeKey;
        if ((*(unsigned char*)(nextNode + 0x0B) & 0x20) == 0 || *nextNode < 2) {
            nextNodeKey = *nextNode;
        } else {
            nextNodeKey = nextNode[1];
        }
        if (nextNodeKey == state[0]) { // matchKey
            return nextKey; // keep currentA pointing to the next node of same key
        }
    }
    // No more matching nodes, invalidate list A
    state[1] = 0;
    return nextKey;

popFromB:
    // Pop from second list (list B)
    if (currentB == nullptr) {
        return 0; // both lists empty
    }
    nextKey = *currentB;
    currentB++;
    state[2] = (int)currentB;

    if (currentB < end) {
        int* nextNode = (int*)*currentB;
        int nextNodeKey;
        if ((*(unsigned char*)(nextNode + 0x0B) & 0x20) == 0 || *nextNode < 4) {
            nextNodeKey = *nextNode;
        } else {
            nextNodeKey = nextNode[5];
        }
        if (nextNodeKey == -1) { // special sentinel key for list B?
            return nextKey; // keep currentB pointing to next -1 key?
        }
    }
    state[2] = 0;
    return nextKey;
}