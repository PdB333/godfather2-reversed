// FUNC_NAME: ObjectPool::allocateNode

// Function at 0x007e8d00: Allocates a node from a fixed-size object pool (12-byte nodes).
// __thiscall: param_1 is the this pointer.
// Node fields: [0x00] unknown, [0x04] unknown, [0x08] nextFree pointer
// Pool fields: [0x08] freeList head, [0x0C] allocatedCount, [0x10] blockListHead

void* __fastcall ObjectPool::allocateNode(int thisPtr)
{
    int *freeHead;
    int *newBlock;
    int *nodeIter;
    int i;

    freeHead = *(int **)(thisPtr + 8); // +0x08: freeList head
    if (freeHead == nullptr)
    {
        // Allocate a new block containing 256 nodes (256 * 12 = 3072 bytes) + 4-byte block header
        newBlock = (int *)FUN_009c8e50(0xc04); // allocate 3076 bytes
        // Initialize free list within the new block
        i = 0xff; // 256 iterations
        nodeIter = newBlock;
        do {
            // Set next pointer (offset 0x08 of node) to the next node address
            // nodeIter[2] would be offset 8; but decompiler shows nodeIter[3] due to pointer increment?
            // Correct: node struct is 3 ints, so next is at index 2 (offset 8).
            // nodeIter[3] is beyond, likely decompiler error; we set nodeIter[2] = nodeIter + 3 (next node)
            nodeIter[2] = (int)(nodeIter + 3); // link to next node
            i--;
            nodeIter = nodeIter + 3; // move to next node (3 ints forward)
        } while (i != 0);
        newBlock[0x300] = 0; // set sentinel at end of block (offset 0xC00) to 0
        // Chain new block into block list: old head stored in node 0 of new block
        newBlock[0] = *(int *)(thisPtr + 0x10); // +0x10: blockListHead -> first node's data
        *(int **)(thisPtr + 0x10) = newBlock;    // update blockListHead
        // Set freeList head to the second node (node 1) of the new block
        *(int **)(thisPtr + 8) = newBlock + 1;   // +0x08: freeList
        freeHead = newBlock + 1;
    }
    // Pop a node from free list
    int *poppedNode = freeHead;
    *(int **)(thisPtr + 8) = (int *)freeHead[2]; // update freeList to next free node
    freeHead[2] = 0;                              // clear next pointer of allocated node
    *(int *)(thisPtr + 0xc) += 1;                 // increment allocated count (+0x0C)
    return poppedNode; // return pointer to allocated node (Ghidra omitted return value)
}