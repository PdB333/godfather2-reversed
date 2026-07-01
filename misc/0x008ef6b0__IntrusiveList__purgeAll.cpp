// FUNC_NAME: IntrusiveList::purgeAll
void __thiscall IntrusiveList::purgeAll(int thisPtr, int param2) {
    int headPtr = thisPtr + 0x20;  // first list head (e.g., sentinel)
    int count = 0;
    int currentThis = thisPtr;
    int local_headAddr;          // reused for heads
    int local_iterData1, local_iterData2; // from getNextPair
    char iteratorBuffer[8];      // iterator state (8 bytes)

    // ------------------------------------------------------------------
    // Phase 1: Find the correct head by trying two possible offsets (0x20 and 0x2c)
    while (count < 2) {
        local_headAddr = headPtr;
        int* iterData = (int*)initializeIterator(iteratorBuffer, &param2); // returns pointer to two ints
        int first = *iterData;
        int second = iterData[1];
        int nextHead = *(int*)(headPtr + 4); // +4 likely offset to first node pointer

        // Validate: first must be non-zero and equal to current head
        if ((first == 0) || (first != local_headAddr)) {
            assertFail(); // FUN_00b97aea
        }
        // second must match the "expected" next pointer from head
        if (second != nextHead) {
            break;
        }
        headPtr = thisPtr + 0x2c; // try second head
        count++;
        local_headAddr = headPtr;
    }

    // After loop, first and second hold values from last successful iteration
    int firstNode = first;   // from inner iterData
    int secondNode = second;
    if (firstNode == 0) {
        assertFail();
    }
    if (secondNode == *(int*)(firstNode + 4)) { // check if second equals prev of first?
        assertFail();
    }

    // ------------------------------------------------------------------
    // Phase 2: Walk the list starting from secondNode->next (offset 0x10)
    int* currentNode = *(int**)(secondNode + 0x10); // list starting pointer (often a node pointer)

    while (true) {
        if (currentNode == nullptr) {
            // No more nodes: switch to a different list (maybe the "free list")
            insertNode(iteratorBuffer, firstNode, secondNode); // FUN_008edd00
            firstNode = thisPtr;
            int savedParam = param2;
            int secondNodeAgain = thisPtr + 0x0C; // another head/offset
            getNextPair(&local_headAddr, &param2); // FUN_008ec8c0
            int a = local_headAddr;
            int b = local_iterData1; // this is set by getNextPair? Actually local_iterData2 is used later.
            // The decompiled uses local_14 and local_10 as outputs
            // We'll adjust variables accordingly

            // Re-simulate the logic after this call
            // This is messy - trust the decompiled flow
            // For simplicity, we'll restructure based on the original code

            // Actually, let's rewrite the inner block more faithfully:

            // After the call:
            int local_14 = local_headAddr;
            int local_10 = local_iterData1; // from getNextPair (second output)
            int iVar1 = firstNode; // == thisPtr
            int iVar7 = secondNodeAgain; // == thisPtr+0x0C
            int iVar5 = *(int*)(iVar1 + 0x10);
            if ((local_14 == 0) || (local_14 != iVar7)) {
                assertFail();
            }
            if (local_10 != iVar5) {
                if (local_14 == 0) {
                    assertFail();
                }
                if (local_10 == *(int*)(local_14 + 4)) {
                    assertFail();
                }
                if (local_10 != -0x10) {
                    param2 = savedParam;
                    getNextPair(&local_headAddr, &param2);
                    local_14 = local_headAddr;
                    iVar5 = *(int*)(iVar1 + 0x10);
                    if ((local_14 == 0) || (local_14 != iVar7)) {
                        assertFail();
                    }
                    if (local_10 != iVar5) {
                        removeNode(iteratorBuffer, local_14, local_10); // FUN_008ed9d0
                    }
                    flushCache(); // FUN_008ef580
                }
            }
            return;
        }

        // Process a node from the list
        int isActive = checkNodeActive(currentNode[6]); // FUN_008ee8b0
        if (isActive == 0) {
            freeNode(currentNode[6]); // FUN_004061b0
        }

        int flag = currentNode[8];
        if ((flag != 0) && (flag != 0x48)) {
            logMessage(&g_logBuffer, flag - 0x0C, 1); // FUN_00408c70
        }

        if (secondNode == *(int*)(firstNode + 4)) {
            assertFail();
        }

        // Unlink the current node from the list
        if (currentNode[1] == 0) {
            // No previous node? (shouldn't happen often)
            int next = currentNode[0];
            *(int*)(secondNode + 0x10) = next;
            if (next != 0) {
                *(int*)(next + 4) = 0; // set next's prev to null
                goto doneUnlink;
            }
    LAB_008ef79a:
            int* prev = (int*)currentNode[1];
            *(int**)(secondNode + 0x14) = prev;
            if (prev != nullptr) {
                *prev = 0;
            }
        } else {
            // Normal doubly-linked list removal
            *(int*)currentNode[1] = currentNode[0];
    doneUnlink:
            if (currentNode[0] == 0) goto LAB_008ef79a;
            *(int*)(currentNode[0] + 4) = currentNode[1];
        }

        currentNode[1] = 0;
        currentNode[0] = 0;

        if (currentNode[8] != 0) {
            clearNodeData(currentNode + 8); // FUN_004daf90
        }
        freeNodeMemory(currentNode); // FUN_009c8eb0

        if (secondNode == *(int*)(firstNode + 4)) {
            assertFail();
        }
        currentNode = *(int**)(secondNode + 0x10); // move to next
    }
}