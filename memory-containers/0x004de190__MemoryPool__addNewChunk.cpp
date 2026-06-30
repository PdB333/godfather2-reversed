// FUNC_NAME: MemoryPool::addNewChunk
// Function address: 0x004DE190
// This function allocates a new chunk of memory and initializes a linked list of fixed-size blocks.
// The chunk is prepended to the free list. The pool structure is described below.

// Memory pool structure (inferred from offsets):
// +0x0C: total allocated memory (sum of blockSize * count)
// +0x14: total free memory (sum of blockSize * count) – identical to above? Possibly a copy.
// +0x18: blockSize (element size)
// +0x1C: blockCount (number of blocks)
// +0x20: alignment offset for data pointer
// +0x28: alignment mask (alignment - 1)
// +0x30: pointer to first free block (head of free list)
// +0x34: pointer to last free block (tail of free list – used for appending new chunks)

// A free block header:
// +0x00: next pointer
// +0x04: prev pointer (if list is doubly linked)

void __fastcall MemoryPool::addNewChunk(int thisPtr)
{
    undefined4 *chunkHeader;
    int *dataPtr;
    int *lastDataPtr;
    int blockSize;
    int alignmentMask;
    int alignmentOffset;

    // Allocate memory for the chunk: blockSize * blockCount + alignment + header overhead
    chunkHeader = (undefined4 *)customAlloc(
        *(int *)(thisPtr + 0x18) * *(int *)(thisPtr + 0x28) + 0x13 +
        *(int *)(thisPtr + 0x20)
    );

    // Initialize chunk header
    chunkHeader[0] = 0;                               // next pointer of new chunk (end of list)
    chunkHeader[1] = *(undefined4 *)(thisPtr + 0x30); // prev pointer = old head

    // If the pool already had a head, link it back to this new chunk
    if (*(void **)(thisPtr + 0x30) != (void *)0x0) {
        **(void ***)(thisPtr + 0x30) = chunkHeader; // old head's prev = new chunk
    }

    // Align the start of data blocks within the chunk
    alignmentOffset = *(int *)(thisPtr + 0x20);
    alignmentMask = *(int *)(thisPtr + 0x28);
    dataPtr = (int *)((alignmentOffset + 0x13 + (int)chunkHeader) & ~(alignmentMask - 1U));

    // Update pool's head pointer to this new chunk
    *(void **)(thisPtr + 0x30) = chunkHeader;
    chunkHeader[2] = dataPtr; // store aligned data start

    // Calculate pointer to the last block in this chunk
    blockSize = *(int *)(thisPtr + 0x18);
    lastDataPtr = (int *)((blockSize - 1) * *(int *)(thisPtr + 0x28) + (int)dataPtr);
    chunkHeader[3] = lastDataPtr;

    // Link the free blocks in this chunk into a singly linked list
    if (dataPtr <= lastDataPtr) {
        int stride = *(int *)(thisPtr + 0x28); // stride is not blockSize? Actually it's alignment? But loop uses blockSize? Let's re-evaluate.
        // The loop uses stride = blockSize? The code: iVar5 = *(int *)(param_1 + 0x28); and then *piVar3 = iVar5 + (int)piVar3; but that would be self-referential? It looks like it stores the next pointer as current address + blockSize.
        // Since iVar5 is *(param_1 + 0x28) = alignment mask? Actually no, the increment is iVar5, which is from +0x28. But it's used as the stride. So better assume +0x28 is the stride (which is actually blockSize maybe duplicate). But earlier alignment mask was from same offset? Possible that this field serves dual purpose? Hard to tell.
        // From context, the loop sets each block's first word to the address of the next block (previous + blockSize). So stride should be blockSize. So I'll use blockSize.
        // However the code uses *(param_1+0x28) for increment, which is also used for alignment mask. So it's likely the same value: blockSize equals alignment mask? Or there's a misidentification. Given the complexity, I'll assume +0x28 is blockSize (stride) and +0x20 is alignment.
        int stride = *(int *)(thisPtr + 0x28); // This might be blockSize, not alignment.
        do {
            *dataPtr = (int)dataPtr + stride; // store next block address
            dataPtr = (int *)((int)dataPtr + stride);
        } while (dataPtr <= lastDataPtr);
    }

    // The last block's next pointer is set to the previous tail of the free list (appending to existing list)
    *(int *)lastDataPtr = *(int *)(thisPtr + 0x34);

    // Store the first data pointer of this chunk as the new free list head? Actually the previous line linked the chunk's end to old tail.
    // Then:
    undefined4 firstBlock = (undefined4)chunkHeader[2]; // aligned first block
    *(int *)(thisPtr + 0x1C) = *(int *)(thisPtr + 0x1C) + 1; // increment block count
    *(int *)(thisPtr + 0x34) = firstBlock; // set tail pointer to the first block of the new chunk? Wait, tail should be last block.
    // Actually the code: *(undefined4 *)(param_1 + 0x34) = uVar1; uVar1 = puVar2[2]; so head becomes the aligned first block.
    // So after this, the free list head is the first block of the new chunk, and the tail is the old tail (or previously stored at +0x34)? No, +0x34 is overwritten.
    // This is confusing. Let's follow the original code exactly:
    // uVar1 = puVar2[2]; <- first aligned block
    // *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + 1;
    // *(undefined4 *)(param_1 + 0x34) = uVar1; // set +0x34 to first block
    // *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + *(int *)(param_1 + 0x18);
    // *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + *(int *)(param_1 + 0x18);
    // So +0x34 becomes the first block (not the last). So it's likely that +0x34 is actually the head of the free list, not tail. But earlier it was used as tail for appending. Possibly the naming is reversed.
    // For clarity, I'll keep the original offsets but note that +0x34 ends up as the first block of the new chunk.

    // Increment internal counters
    *(int *)(thisPtr + 0x14) += *(int *)(thisPtr + 0x18);
    *(int *)(thisPtr + 0x0c) += *(int *)(thisPtr + 0x18);
}