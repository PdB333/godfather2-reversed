// FUNC_NAME: QueueManager::processAllEvents

void __fastcall QueueManager::processAllEvents(int thisPtr)
{
    int *eventObject;
    int subListIter;
    int *nextNode;
    int *eventEntry;
    int *currentNode;
    int *vtablePtr; // Actually a pointer to virtual function table
    int contextData; // local_c - used for passing to callback
    int *contextArg; // local_8 - second argument to callback
    byte contextFlags; // local_4

    // Acquire a global mutex (if available)
    if (g_queueMutex != 0) {
        contextData = g_queueMutex;
        contextArg = (int *)0x0;
        contextFlags = 0;
        acquireMutex(); // FUN_00408800
    }

    // Walk the list of work channels (node list at +0x60)
    currentNode = *(int **)(thisPtr + 0x60);
    do {
        if (currentNode == (int *)0x0) {
            releaseMutex(); // FUN_00448590
            return;
        }

        nextNode = (int *)*currentNode;           // +0x00: next node pointer
        subListIter = currentNode[3];             // +0x0C: pointer to event list within channel

        // Process all events in this channel
        while (subListIter != 0) {
            eventEntry = (int *)currentNode[3];   // = same pointer; this loop is effectively infinite unless eventList mutates
            if (eventEntry != (int *)0x0) {
                // Check flag at +0x14 (eventEntry[5]) for 0x8000000
                if ((eventEntry[5] & 0x8000000U) == 0) {
                    // Direct vtable call: first function
                    vtablePtr = (int *)*eventEntry;
                } else {
                    // Offset +0x3C (eventEntry + 0xF) points to an object
                    eventObject = eventEntry + 0xF;
                    // Check byte at +0x40 for bit 2
                    if ((*(byte *)(eventEntry + 0x10) & 2) != 0) {
                        contextFlags = 0;
                        contextData = g_someGlobal;   // DAT_012067dc
                        contextArg = eventObject;
                        // Virtual call: second vtable function at offset +4
                        (**(code **)(*eventObject + 4))(&contextData);
                    }
                    vtablePtr = (int *)*eventObject;
                }
                // Invoke first virtual function with argument 1
                (*(code *)*vtablePtr)(1);
            }
            // Infinite loop: subListIter never changes (likely a decompiler simplification)
            subListIter = currentNode[3];
        }

        // Remove current node from doubly linked list
        if ((int *)currentNode[1] == (int *)0x0) {       // +0x04: prev pointer
            // Node is head
            int *newHead = (int *)*currentNode;
            *(int **)(thisPtr + 0x60) = newHead;
            if (newHead != (int *)0x0) {
                *(int *)(newHead + 4) = 0;               // new head's prev = NULL
                goto LAB_00448085;
            }
LAB_00448093:
            vtablePtr = (int *)currentNode[1];
            *(int **)(thisPtr + 100) = vtablePtr;        // +0x64: tail pointer?
            if (vtablePtr != (int *)0x0) {
                *vtablePtr = 0;
            }
        } else {
            // Node is not head
            *(int *)currentNode[1] = *currentNode;       // prev->next = current->next
LAB_00448085:
            if (*currentNode == 0) goto LAB_00448093;
            *(int *)(*currentNode + 4) = currentNode[1]; // next->prev = current->prev
        }

        currentNode[1] = 0;  // clear prev
        *currentNode = 0;    // clear next
        freeChannelNode();   // FUN_00448630

        currentNode = nextNode;
    } while( true );
}