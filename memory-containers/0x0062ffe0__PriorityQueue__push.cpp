//FUNC_NAME: PriorityQueue::push
// Function at 0x0062ffe0: Insert an element into a binary heap priority queue.
// The heap stores 8-byte entries (priority + data). The class has:
//   +0x08: m_pEnd (pointer to one past last element)
//   +0x0c: m_pStart (pointer to first element)
// The heap uses a sentinel at index 0 with priority == 5.
// Called functions: assert, getRandomInt, getRandomFloat, resizeHeap, allocNode, insertNode, getRootNode.

int PriorityQueue::push(int thisPtr)
{
    int *pEnd = *(int **)(thisPtr + 8);   // +0x08: m_pEnd
    int *pStart = *(int **)(thisPtr + 0xc); // +0x0c: m_pStart

    // Validate heap: must not be empty and first element's priority must be 5 (sentinel)
    if ((pEnd <= pStart) || (pStart == nullptr) || (*pStart != 5)) {
        FUN_00627ac0(PTR_s_table_00e2a8b0); // assertion failure
    }

    int currentSize = FUN_00628820(1); // get current number of elements? returns something +1
    int newSize = currentSize + 1;

    int insertIndex; // index where new element will be inserted
    int parentIndex; // parent index for bubble-up

    if (((int)pEnd - (int)pStart) >> 3 == 2) { // if heap has exactly 2 elements (excluding sentinel?)
        parentIndex = 2;
        insertIndex = newSize;
    } else {
        float randomFloat = FUN_00628080(); // get a random float
        insertIndex = (int)randomFloat;
        parentIndex = 3;
        if (newSize < insertIndex) {
            newSize = insertIndex;
        }
    }

    FUN_006286b0(newSize); // resize heap to newSize capacity

    int i = newSize;
    while (i = i - 1, insertIndex <= i) {
        // Allocate a new node (or get a temporary buffer)
        int *newNode = (int *)FUN_00637f10();
        int *currentEnd = *(int **)(thisPtr + 8);
        *currentEnd = *newNode;
        currentEnd[1] = newNode[1];
        *(int *)(thisPtr + 8) = *(int *)(thisPtr + 8) + 8; // advance end

        int newEnd = *(int *)(thisPtr + 8);
        int sentinelData = *(int *)(*(int *)(thisPtr + 0xc) + 4); // second word of sentinel

        int *tempNode = (int *)FUN_00637f10();
        if (tempNode == &DAT_00e2a93c) { // sentinel check (maybe indicates failure)
            float f = (float)newSize;
            int local3 = 3;
            tempNode = (int *)FUN_00637d60(thisPtr, sentinelData, &local3);
        }

        newSize = newSize - 1;
        *tempNode = *(int *)(newEnd - 8);
        tempNode[1] = *(int *)(newEnd - 4);
        *(int *)(thisPtr + 8) = *(int *)(thisPtr + 8) - 8; // retreat end
    }

    // Get the element to insert (either from root or from computed position)
    int *sourceNode;
    if (parentIndex == 0) {
        sourceNode = (int *)FUN_00625430(); // get root node?
    } else {
        sourceNode = (int *)(*(int *)(thisPtr + 0xc) + -8 + parentIndex * 8);
    }

    // Copy source node to end
    int *currentEnd2 = *(int **)(thisPtr + 8);
    *currentEnd2 = *sourceNode;
    currentEnd2[1] = sourceNode[1];
    *(int *)(thisPtr + 8) = *(int *)(thisPtr + 8) + 8;

    int sentinelData2 = *(int *)(*(int *)(thisPtr + 0xc) + 4);
    int newEnd2 = *(int *)(thisPtr + 8);
    int *tempNode2 = (int *)FUN_00637f10();
    if (tempNode2 == &DAT_00e2a93c) {
        float f = (float)insertIndex;
        int local3 = 3;
        tempNode2 = (int *)FUN_00637d60(thisPtr, sentinelData2, &local3);
    }
    *tempNode2 = *(int *)(newEnd2 - 8);
    tempNode2[1] = *(int *)(newEnd2 - 4);
    *(int *)(thisPtr + 8) = *(int *)(thisPtr + 8) - 8;

    return 0;
}