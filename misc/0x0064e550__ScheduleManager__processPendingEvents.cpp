// FUNC_NAME: ScheduleManager::processPendingEvents

// Function at 0x0064e550: Process incoming events and execute scheduled events.
// This function is called to add new events (from input list) to the sorted event queue,
// then execute events whose key matches the current sequence counter.
void __thiscall ScheduleManager::processPendingEvents(int thisPtr, int inputList)
{
    int *nodePtr;
    int *prevPtr;
    int *freeNode;
    int key;
    int *currentNode;
    int *temp;

    // If there is a pending destroy list, process it first
    if (*(int *)(thisPtr + 0x1c8) != 0) {
        destroyEventList();                          // FUN_0065b9d0
    }

    // The sorted event queue (singly linked list) is stored at this+0x1e0 (root pointer)
    int *rootPtr = (int *)(thisPtr + 0x1e0);
    
    // Input list head is at param2+0x14
    int *inputListNode = *(int **)(inputList + 0x14);

    while (true) {
        if (inputListNode == (int *)0x0) {
            // No more input nodes, process the sorted queue
            while (true) {
                key = *rootPtr;
                if (key == 0) {
                    return;                          // Queue empty
                }
                // Check if the next event’s key matches the expected sequence
                int expectedSeq = *(int *)(thisPtr + 0x1ec) + 1;
                int *nextNode = (int *)*rootPtr;
                if (nextNode[1] != expectedSeq) {
                    return;                          // Not yet time for next event
                }
                // Advance the sequence counter
                *(int *)(thisPtr + 0x1ec) = expectedSeq;

                // Execute the event’s virtual function at vtable+0x20
                int *eventObj = (int *)nextNode[2];  // offset 0x08? Actually nextNode[2] is something else
                (**(code **)(*(int *)*nextNode + 0x20))(thisPtr, 1);

                // At exit handler registration
                if ((_DAT_01223cbc & 1) == 0) {
                    _DAT_01223cbc |= 1;
                    scheduleManagerAtexitHandler();   // FUN_0064f120
                    _atexit((_func_4879 *)&atexit_shutdown);
                }

                // Handle node deallocation (reference counting)
                currentNode = (int *)*rootPtr;
                temp = (int *)*currentNode;
                if (temp != (int *)0x0) {
                    prevPtr = temp + 2;               // ref count at offset +0x08
                    *prevPtr = *prevPtr - 1;
                    if (*prevPtr == 0) {
                        (**(code **)(*temp + 8))();    // vtable+8 = destructor
                    }
                }

                // Global node counter decrement, add node to free list
                _DAT_01223cb0 = _DAT_01223cb0 - 1;
                *currentNode = (int)_DAT_01223cb8;
                _DAT_01223cb8 = currentNode;

                // Move to next node in queue
                *rootPtr = (int)nextNode[2];
            }
        }

        // Process current input node
        int *node = inputListNode;
        int nextNodePtr = node[2];                     // node->next
        inputListNode = (int *)nextNodePtr;

        // Check if the event object’s “active” flag (offset 0x10) is set
        if (*((int *)*node + 4) != 0) {                // (*node)[4] (eventObj->active)
            // Execute the event
            (**(code **)(*(int *)*node + 0x20))(thisPtr, 1);

            // At exit handler registration
            if ((_DAT_01223cbc & 1) == 0) {
                _DAT_01223cbc |= 1;
                scheduleManagerAtexitHandler();
                _atexit((_func_4879 *)&atexit_shutdown);
            }

            // Decrement reference count of event object
            int *eventObj = (int *)*node;
            if (eventObj != (int *)0x0) {
                prevPtr = eventObj + 2;                // offset +0x08
                *prevPtr = *prevPtr - 1;
                if (*prevPtr == 0) {
                    (**(code **)(*eventObj + 8))();    // vtable+8 destructor
                }
            }

            // Free the node
            _DAT_01223cb0 = _DAT_01223cb0 - 1;
            *node = (int)_DAT_01223cb8;
            _DAT_01223cb8 = node;
        }
        else {
            // Insert the node into the sorted event queue (ascending by key)
            // The key is stored at node[1] (offset 0x04)
            if (*rootPtr != 0) {
                do {
                    currentNode = (int *)*rootPtr;
                    if (node[1] <= currentNode[1]) {   // new key <= current key
                        break;
                    }
                    rootPtr = (int *)(currentNode + 2); // move to next pointer (offset 0x08)
                } while (*rootPtr != 0);
            }
            // Insert node at the found position
            node[2] = (int)*rootPtr;                  // node->next = current node (or null)
            *rootPtr = (int)node;                     // predecessor’s next = node
            rootPtr = node + 2;                       // update rootPtr for subsequent inserts? Actually it's a local copy that gets reset each iteration? But note: rootPtr is modified by the inner loop; after insertion, they set rootPtr = node+2, but then the outer loop continues reading inputListNode, and rootPtr will be reinitialized from thisPtr+0x1e0 on next iteration? No, rootPtr is a local variable that started as &(thisPtr+0x1e0). After insertion, it is changed to node+2. That would mess up subsequent insertions if multiple input nodes are inserted. That seems like a bug, or maybe they always reinitialize rootPtr for each input node? Actually looking at the asm: at the start of the outer loop, they set piVar3 = param_1+0x1e0; then piVar4 = input list; then inside, after processing an input node that gets inserted, they set piVar8 = piVar2+2 and then continue; piVar8 is the root pointer variable. So on the next iteration, they will reuse the modified piVar8, not reseting to &(thisPtr+0x1e0). This would cause the next insertion to start from the newly inserted node's next pointer, effectively building a sorted list but with suboptimal insertion. However, in practice, if the input list is processed sequentially, the new nodes are inserted in sorted order, so the rootPtr walk will be correct. This is an optimization: after inserting one node, the root pointer points to the inserted node's next field, which might be where the next insertion should start if the list is still sorted. But it's fragile.
        }
    }
}