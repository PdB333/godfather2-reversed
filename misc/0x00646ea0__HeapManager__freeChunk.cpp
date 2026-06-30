// FUNC_NAME: HeapManager::freeChunk
void HeapManager::freeChunk(HeapManager* heap, void* block)
{
    uint* header;
    uint* chunkPtr;
    uint size;
    uint binIndex;
    void* topChunk;
    uint uVar4;
    uint uVar7;
    uint* ucPtr;
    int* nextFree;
    int* prevFree;
    char cVar6;
    uint uVar9;

    if (block != 0) {
        header = (uint*)((int)block - 4);
        chunkPtr = (uint*)((int)block - 8);
        size = *header & 0x7ffffff8; // Mask out status flags, get aligned size
        binIndex = size >> 3; // Index into small bin array (8-byte aligned bins)

        if ((size <= *(uint*)(heap + 4)) &&
            (*(uint**)(heap + 0x468) == 0 || chunkPtr < *(uint**)(heap + 0x468))) {
            // Fast path: small chunk, put into appropriate small bin
            *(uint*)(heap + 4) |= 1; // Set flag indicating small bin usage
            // Insert into bin list (singly linked list of free chunks)
            *(uint*)(chunkPtr - 1) = *(uint*)(heap + binIndex * 4); // prev_size? Actually this is at offset -4 from chunk
            *header |= 0x80000004; // Set flags: 0x80000004 = (INUSE | PREV_INUSE?)
            *(undefined4*)((int)block + 4) = *(undefined4*)(heap + binIndex * 4); // Next chunk pointer? Wait, block+4 is user data, but maybe it's the fd/bk? Actually this is messy.
            *(uint**)(heap + binIndex * 4) = chunkPtr;
            return;
        }

        // Not a fast path
        if ((*header & 2) == 0) { // Not mmapped chunk
            // Coalesce with previous chunk if free
            ucPtr = (uint*)((int)chunkPtr + size);
            uVar7 = *(uint*)((int)chunkPtr + size + 4) & 0x7ffffff8; // Next chunk's size
            if ((*header & 1) == 0) { // Previous chunk is free
                // Unlink previous chunk
                size += *chunkPtr;
                chunkPtr = (uint*)((int)chunkPtr - *chunkPtr);
                *(uint*)(chunkPtr + 1) = size | 1; // Set size and PREV_INUSE flag
                *ucPtr = size; // Footer? Actually dlmalloc stores size at end
                // Update linked list of free chunks: unlink
                *(uint*)(*(uint*)(chunkPtr + 2) + 0xc) = *(uint*)(chunkPtr + 3);
                *(uint*)(*(uint*)(chunkPtr + 3) + 8) = *(uint*)(chunkPtr + 2);
            }

            // Coalesce with next chunk if free
            if ((*(uint*)((int)ucPtr + uVar7 + 4) & 1) == 0) { // Next chunk is free
                // Unlink next chunk
                *(uint*)(*(uint*)(ucPtr + 2) + 0xc) = *(uint*)(ucPtr + 3);
                *(uint*)(*(uint*)(ucPtr + 3) + 8) = *(uint*)(ucPtr + 2);
                size += uVar7;
                *(uint*)(chunkPtr + 1) = size | 1;
                *(uint*)((int)chunkPtr + size) = size; // Footer
            } else {
                *(uint*)(ucPtr + 1) &= 0xfffffffe; // Clear PREV_INUSE of next chunk
                *ucPtr = size; // Store size in footer? Actually in dlmalloc the footer is the next chunk's prev_size
            }

            // Insert into unsorted bin or small bin
            if (chunkPtr == *(uint**)(heap + 0x440) || ucPtr == *(uint**)(heap + 0x440)) {
                *(uint**)(heap + 0x440) = chunkPtr; // Update last reminder? Actually +0x440 is "last_reminder" in dlmalloc
                FUN_00644ae0(heap); // likely handle top chunk extension
            } else if (*(char*)(heap + 0x46e) == '\0') { // Flag for normal operation
                FUN_00646c60(heap, chunkPtr); // Insert into regular bin (by size)
            } else {
                // Insert into unsorted bin list (linked list at heap+0x30)
                uVar4 = *(uint*)(heap + 0x3c);
                *(uint*)(chunkPtr + 2) = heap + 0x30; // fd pointer
                *(uint*)(chunkPtr + 3) = uVar4; // bk pointer
                *(uint**)(heap + 0x3c) = chunkPtr;
                *(uint**)(uVar4 + 8) = chunkPtr;
            }

            // Check if the total size of freed chunk exceeds a threshold, and if so, return memory to OS
            if ((0xffff < size) && (cVar6 = FUN_00644920(), cVar6 != '\0') &&
                (*(uint*)(heap + 0x4c8) <= size)) {
                FUN_006484b0(heap, *(undefined4*)(heap + 0x4cc)); // Trim or release to OS
                return;
            }
        } else {
            // Chunk is mmapped, free it directly
            uVar4 = *chunkPtr; // size of mmapped region (including header)
            nextFree = (int*)((int)chunkPtr + 0xc + size);
            prevFree = (int*)((int)chunkPtr + 8 + size);
            // Remove from mmapped list? Actually these pointers are for a doubly linked list of mmapped chunks
            *(int*)(*nextFree + 0xc) = *prevFree;
            *(int*)(*prevFree + 8) = *nextFree;
            *(int*)(heap + 0x48c) -= (uVar4 + 0x10 + size); // Update total free space
            *(int*)(heap + 0x488) += -1; // Decrement number of free chunks
            VirtualFree((LPVOID)((int)chunkPtr - uVar4), 0, 0x8000); // Free the memory from OS
        }
    }
    return;
}