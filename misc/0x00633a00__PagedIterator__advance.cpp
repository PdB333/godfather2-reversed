// FUNC_NAME: PagedIterator::advance
void __thiscall PagedIterator::advance(void)
{
    uint flags = *(uint *)(this + 0x30); // +0x30
    if (((flags & 8) != 0) && (*(int *)(this + 0x38) == 0)) {
        *(int *)(this + 0x38) = *(int *)(this + 0x34); // +0x34 -> +0x38
        FUN_00635d00(0xffffffff); // reset with sentinel
        return;
    }
    if ((flags & 4) == 0) {
        return;
    }
    int *pBlockData = *(int **)(this + 0x14); // +0x14: pointer to an array of ints
    int *containerRoot = (int *)*pBlockData; // first element of block
    // containerRoot points to some allocation header; subtract 4 to get vtable pointer?0
    int nodePtr = *(int *)(*(int *)((int)containerRoot - 4) + 0xc); // +0xc inside some meta
    int currentNode = (int)nodePtr;
    int currentEnd;
    if (*(int *)(currentNode + 0x14) == 0) {
        currentEnd = 0;
    } else {
        // Scary pointer arithmetic to get a slot from an array
        currentEnd = *(int *)(*(int *)(currentNode + 0x14) - 4 + ((pBlockData[4] - *(int *)(currentNode + 0xc)) >> 2) * 4);
    }
    if (*(char *)(this + 0x32) == '\0') { // +0x32: useNextPage flag
        FUN_00632ae0(); // fetch next page
        return;
    }
    uint *puEndPtr = (uint *)pBlockData[4]; // treat as pointer to uint
    if ((int)(*puEndPtr - *(int *)(currentNode + 0xc)) >> 2 == 1) {
        pBlockData[3] = *puEndPtr; // set current index to next slot
    }
    if ((uint)pBlockData[3] < *puEndPtr) {
        int nextNode;
        if (*(int *)(currentNode + 0x14) == 0) {
            nextNode = 0;
        } else {
            nextNode = *(int *)(*(int *)(currentNode + 0x14) - 4 + ((pBlockData[3] - *(int *)(currentNode + 0xc)) >> 2) * 4);
        }
        if (currentEnd != nextNode) {
            FUN_00635d00(currentEnd); // signal node change
            pBlockData = *(int **)(this + 0x14); // reload after call
        }
    }
    pBlockData[3] = *(int *)pBlockData[4]; // advance current index
    return;
}