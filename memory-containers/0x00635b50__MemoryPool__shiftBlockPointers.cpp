// FUNC_NAME: MemoryPool::shiftBlockPointers
void __fastcall MemoryPool::shiftBlockPointers(int thisPtr, int oldBase)
{
    int *blockPtr;
    int **iter;

    // Adjust the free list head pointer: shift it relative to new base
    *(int *)(thisPtr + 8) = *(int *)(thisPtr + 0x1c) + (*(int *)(thisPtr + 8) - oldBase >> 3) * 8;

    // Adjust all entries in the singly-linked free list (each node points to next via first field)
    for (int *node = *(int **)(thisPtr + 0x48); node != nullptr; node = (int *)*node) {
        node[2] = *(int *)(thisPtr + 0x1c) + (node[2] - oldBase >> 3) * 8;
    }

    // Adjust all allocated blocks in the range [start, end) (each block is 6 ints wide)
    iter = *(int **)(thisPtr + 0x28);
    if (iter <= *(int **)(thisPtr + 0x14)) {
        do {
            iter[1] = *(int *)(thisPtr + 0x1c) + (iter[1] - oldBase >> 3) * 8;
            *iter = *(int *)(thisPtr + 0x1c) + (*iter - oldBase >> 3) * 8;
            iter += 6;
        } while (iter <= *(int **)(thisPtr + 0x14));
    }

    // Update the first allocated block pointer from the start of the range
    *(int *)(thisPtr + 0xc) = **(int **)(thisPtr + 0x14);
}