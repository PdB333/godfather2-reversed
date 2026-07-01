// FUNC_NAME: FourKeyLinkedList::FindAndRemoveNode
// Function at 0x00867690
// Searches a circular linked list with 4 keys (at offsets +0x00, +0x08, +0x0C, +0x14) and a next pointer at +0x1C.
// If a node is found, the low byte of the return value is set to 1; if found but the third key (+0x0C) is zero, the node is removed from the list.
// The output next pointer (param_7) is updated to the successor of the current node after each step.
uint __thiscall FourKeyLinkedList::FindAndRemoveNode(
    void *this,                     // param_1: this pointer (passed to helper)
    int key1,                       // param_2: value to compare against node->key0 (+0x00)
    int key2,                       // param_3: value to compare against node->key2 (+0x08)
    int key3,                       // param_4: value to compare against node->key3 (+0x0C)
    int key4,                       // param_5: value to compare against node->key5 (+0x14)
    int **head,                     // param_6: pointer to head pointer of the list
    int *outNext                    // param_7: output – next pointer of the examined node
)
{
    int *nodePtr;
    int *origHead;
    int nextStore;                  // local to hold next pointer before returning
    void *thisCopy;

    // Initialize: start at the head of the list
    nodePtr = *head;
    *outNext = (int)nodePtr;
    origHead = *head;
    thisCopy = this;

    do {
        if (nodePtr == (int*)0) break;

        if (*nodePtr == 0) {
            // Node's first key is zero: remove it and continue
            if (nodePtr == (int*)0) {
                nextStore = 0;
            } else {
                nextStore = nodePtr[7]; // next at offset +0x1C
            }
            *outNext = nextStore;
            RemoveNode(thisCopy, &nodePtr); // actually removes node pointed by nodePtr
        } else {
            // Check if all four keys match
            if ((key1 == *nodePtr) && (key2 == nodePtr[2]) && (key3 == nodePtr[3]) && (key4 == nodePtr[5])) {
                if (nodePtr[3] == 0) {
                    // Third key is zero: remove the node and output next pointer
                    if (nodePtr == (int*)0) {
                        *outNext = 0;
                    } else {
                        *outNext = nodePtr[7];
                    }
                    RemoveNode(thisCopy, &nodePtr);
                } else {
                    // Node found and valid, return the node address with low bit set
                    return (uint)((uint)nodePtr & 0xFFFFFF00) | 1;
                }
            } else {
                // No match, update output next pointer to node's successor
                if (nodePtr == (int*)0) {
                    *outNext = 0;
                } else {
                    *outNext = nodePtr[7];
                }
            }
        }

        // Advance to next node
        nodePtr = (int*)*outNext;
    } while (nodePtr != origHead);

    // Not found: return 0 (or last examined pointer with low byte cleared)
    return (uint)nodePtr & 0xFFFFFF00;
}