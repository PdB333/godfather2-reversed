// FUNC_NAME: ObjectPool::initialize
void __thiscall ObjectPool::initialize(void)
{
    int *poolBase;
    int *nodePtr;
    int i;

    // Allocate memory for pool: 0x3004 bytes (header + 1024 nodes of 12 bytes each)
    poolBase = (int *)FUN_009c8e50(0x3004);
    if (poolBase != (int *)0x0) {
        // Zero out the 'next' field (offset 4 from node start) for each node
        // Nodes are 12 bytes apart, starting at offset 4 (after header)
        nodePtr = poolBase + 1;  // First node at offset 4
        i = 0x3ff;  // 1023 iterations (0x3ff+1 = 1024)
        do {
            *nodePtr = 0;        // node->field1 = 0 (offset 4 from pool base)
            nodePtr = nodePtr + 3; // advance 12 bytes to next node
            i = i + -1;
        } while (-1 < i);
    }

    // Build linked list: each node's next pointer (offset 8 from node) points to next node
    // Also sets header's next pointer (offset 12) to first node
    i = 0x3ff;
    nodePtr = poolBase;  // Start at header (offset 0)
    do {
        // nodePtr[3] is at offset 12 from pool base (i.e., node's next pointer at offset 8 from node)
        // Set it to address of next node (offset 16 from pool base = nodePtr+4)
        nodePtr[3] = (int)(nodePtr + 4);
        i = i + -1;
        nodePtr = nodePtr + 3; // advance 12 bytes
    } while (i != 0);

    // Store tail pointer? (offset 0x3000 from pool base)
    poolBase[0xc00] = *(int *)(this + 8);  // this->freeListHead stored at end of pool
    // Store head pointer? (offset 0 from pool base)
    *poolBase = *(int *)(this + 0x10);     // this->poolBase stored at header

    // Update object's pointers
    *(int **)(this + 0x10) = poolBase;     // this->poolBase = poolBase
    *(int **)(this + 8) = poolBase + 1;    // this->freeListHead = first node (offset 4)
    return;
}