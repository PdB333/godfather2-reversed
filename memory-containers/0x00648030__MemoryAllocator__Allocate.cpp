// FUNC_NAME: MemoryAllocator::Allocate
// Address: 0x00648030
// Role: Custom heap allocator (EARS engine memory pool)
// Structure fields (relative to this):
// +0x30: Free list head (sentinel)
// +0x3c: Free list tail (sentinel)
// +0x440: Current free block pointer (first free)
// +0x448: End sentinel for segment list
// +0x460: Segment list (large blocks from VirtualAlloc)
// +0x468: Top pointer for next allocation (if not fixed)
// +0x46c: Bool flag (if false, update top pointer)
// +0x4e0: Minimum allocation size threshold

void __thiscall MemoryAllocator::Allocate(uint size)
{
    uint allocatedSize;
    int *block;
    int *prevBlock;
    int iVar4;
    int iVar5;
    uint uVar6;
    uint uVar9;
    uint uVar10;
    uint uVar11;
    uint uVar12;
    int *nextSegment;
    int *segment;
    bool bIsFirstFreeBlock;

    allocatedSize = 0;
    bIsFirstFreeBlock = false;

    // Walk through segments (large blocks allocated via VirtualAlloc)
    segment = *(int **)(this + 0x460); // first segment
    while (segment != (int *)(this + 0x448)) // end sentinel
    {
        uint segmentAvail = segment[2] - segment[1]; // segment[1] is free offset, segment[2] is end
        if (size <= segmentAvail)
        {
            allocatedSize = size;
            if (size < *(uint *)(this + 0x4e0)) // enforce minimum allocation size
            {
                allocatedSize = *(uint *)(this + 0x4e0);
            }
            if (segmentAvail < allocatedSize)
            {
                allocatedSize = segmentAvail;
            }

            LPVOID pvVar7 = VirtualAlloc(
                (LPVOID)(segment[1] + (int)segment), // address after segment header
                allocatedSize,
                0x1000, // MEM_COMMIT
                4       // PAGE_READWRITE
            );
            if (pvVar7 == NULL)
            {
                segment[2] = segment[1]; // mark segment as full
            }
            break;
        }
        segment = (int *)segment[6]; // next segment (linked list at offset 6)
    }

    if (segment != (int *)(this + 0x448))
    {
        int freeOffset = segment[1];
        int remaining = allocatedSize;
        if (freeOffset == 0) // first allocation in this segment
        {
            // Align the start of the segment's heap space
            int *newBlock = (int *)(((int)segment + 0x27) & 0xfffffff8);
            uint heapEnd = (int)segment + (allocatedSize - (int)newBlock);
            segment[0] = (int)newBlock; // store start of heap area
            uint sizeAligned = heapEnd & 0x7ffffff8;
            uint sizeWithOverhead = sizeAligned - 0x10; // 0x10 = block header size?

            newBlock[1] = (heapEnd & 0x80000007) | 1 | sizeWithOverhead; // set size with flags
            newBlock[0] = 0; // previous free block
            *(uint *)(sizeWithOverhead + (int)newBlock) = sizeWithOverhead; // trailer size
            *(int *)((sizeAligned - 0xc) + (int)newBlock) = 8; // debug magic?
            *(int *)((sizeAligned - 8) + (int)newBlock) = 8;
            *(int *)((sizeAligned - 4) + (int)newBlock) = 9;

            // Insert block into free list
            int oldBlock = *(int *)(this + 0x440);
            *(int **)(this + 0x440) = newBlock;
            newBlock[3] = (int)newBlock; // set self as next?
            *(int *)(*(int *)(this + 0x440) + 8) = *(int *)(*(int *)(this + 0x440) + 0xc); // copy next/prev?

            if (oldBlock != this + 0x30) // not the sentinel head
            {
                iVar5 = *(int *)(this + 0x3c); // free list tail
                *(int *)(oldBlock + 8) = this + 0x30; // old block's next = head
                *(int *)(oldBlock + 0xc) = iVar5; // old block's prev = tail
                *(int *)(this + 0x3c) = oldBlock; // update tail
                *(int *)(iVar5 + 8) = oldBlock; // old tail's next = oldBlock
            }

            if (*(char *)(this + 0x46c) == '\0') // if not fixed pool
            {
                // Update top pointer for next allocation (based on size)
                *(uint *)(this + 0x468) =
                    (*(uint *)(*(int *)(this + 0x440) + 4) >> 1 & 0x3ffffffc) +
                    *(int *)(this + 0x440);
            }
            bIsFirstFreeBlock = true;
        }
        else
        {
            // Try to merge with previous free block
            int *prevBlock = (int *)(freeOffset - 0x10 + (int)segment); // header of previous block?
            if ((*(byte *)(freeOffset - 0xc + (int)segment) & 1) == 0) // previous block is free
            {
                int *mergedBlock = (int *)((int)prevBlock - *prevBlock); // go to start of merged block
                // Remove merged block from free list
                *(int *)(mergedBlock[2] + 0xc) = mergedBlock[3];
                *(int *)(mergedBlock[3] + 8) = mergedBlock[2];
                remaining = *prevBlock + allocatedSize;
                mergedBlock[1] = remaining | 1; // set size with allocated bit
                bIsFirstFreeBlock = (mergedBlock == *(int **)(this + 0x440));
            }
            else
            {
                // Allocate at current free offset
                prevBlock[1] = allocatedSize | 1;
                mergedBlock = prevBlock;
            }

            uint *trailer = (uint *)(remaining + (int)mergedBlock);
            trailer[0] = remaining; // trailer size
            trailer[1] = 8;
            trailer[2] = 8;
            trailer[3] = 9;
        }

        segment[1] = segment[1] + allocatedSize; // advance free offset
        if (mergedBlock != (int *)0x0)
        {
            goto LAB_00648247;
        }
    }

    // No space in existing segments, allocate a new segment
    mergedBlock = (int *)FUN_006482d0(0); // create new segment (probably calls VirtualAlloc)
    if (mergedBlock == (int *)0x0)
    {
        return;
    }

    iVar4 = *(int *)(this + 0x440);
    *(int **)(this + 0x440) = mergedBlock;
    mergedBlock[3] = (int)mergedBlock;
    *(int *)(*(int *)(this + 0x440) + 8) = *(int *)(*(int *)(this + 0x440) + 0xc);
    if (iVar4 != this + 0x30)
    {
        iVar5 = *(int *)(this + 0x3c);
        *(int *)(iVar4 + 8) = this + 0x30;
        *(int *)(iVar4 + 0xc) = iVar5;
        *(int *)(this + 0x3c) = iVar4;
        *(int *)(iVar5 + 8) = iVar4;
    }
    if (*(char *)(this + 0x46c) == '\0')
    {
        *(uint *)(this + 0x468) =
            (*(uint *)(*(int *)(this + 0x440) + 4) >> 1 & 0x3ffffffc) +
            *(int *)(this + 0x440);
    }
    bIsFirstFreeBlock = true;
    remaining = mergedBlock[1] & 0x7ffffff8;

LAB_00648247:
    if (size < remaining)
    {
        // Split block
        mergedBlock[1] = size | 1;
        uint *nextBlock = (uint *)((int)mergedBlock + size);
        remaining -= size;
        nextBlock[0] = size; // previous size?
        nextBlock[1] = remaining;
        *(uint *)(remaining + (int)nextBlock) = remaining; // trailer

        if (bIsFirstFreeBlock)
        {
            *(uint **)(this + 0x440) = nextBlock;
            nextBlock[3] = (uint)nextBlock;
            *(int *)(*(int *)(this + 0x440) + 8) = *(int *)(*(int *)(this + 0x440) + 0xc);
            if (*(char *)(this + 0x46c) == '\0')
            {
                *(uint *)(this + 0x468) =
                    (*(uint *)(*(int *)(this + 0x440) + 4) >> 1 & 0x3ffffffc) +
                    *(int *)(this + 0x440);
                return;
            }
        }
        else
        {
            // Insert the new free block into the free list
            uint *tail = *(uint **)(this + 0x3c);
            nextBlock[2] = (uint)(this + 0x30); // next = head
            nextBlock[3] = (uint)tail; // prev = tail
            *(uint **)(this + 0x3c) = nextBlock;
            *(uint **)(tail + 8) = nextBlock;
        }
    }
    // Otherwise, use the whole block (no split)
    return;
}