// FUNC_NAME: MemoryPool::allocateBlock
// Address: 0x0056e5e0
// This function allocates a block of size param_2 from a memory pool.
// It manages a doubly-linked list of free blocks and a separate linked list of used blocks.
// The pool can reclaim blocks if they are no longer referenced (checked via reference flags at offset +0x9 of referenced objects).
// Returns 1 on success (sets *outOffset to the start offset), 0 on failure.

int __thiscall MemoryPool::allocateBlock(int thisPtr, uint size, int *outOffset)
{
    int *node;
    int extraVar;
    bool ref1, ref2, ref3;
    int accumulatedSize;
    
    *outOffset = 0;
    
    // If current offset + size would exceed the total pool capacity, try to reclaim blocks
    if (*(uint *)(thisPtr + 0x24) < *(int *)(thisPtr + 0x28) + size) {
        // Walk the active list (list of blocks already allocated?) and try to reclaim
        if ((uint)(*(int *)(thisPtr + 0x20) + *(int *)(thisPtr + 0x28)) <= 
            *(uint *)(*(int *)(thisPtr + 0x14) + 0x20)) {
            do {
                node = *(int **)(thisPtr + 0x14);
                extraVar = *node;
                *(int *)(thisPtr + 0x14) = extraVar;
                *(undefined4 *)(extraVar + 4) = 0;
                node[1] = *(int *)(thisPtr + 0x18);
                **(undefined4 **)(thisPtr + 0x18) = node;
                *node = 0;
                *(int **)(thisPtr + 0x18) = node;
            } while ((uint)(*(int *)(thisPtr + 0x28) + *(int *)(thisPtr + 0x20)) <= 
                     *(uint *)(*(int *)(thisPtr + 0x14) + 0x20));
        }
        *(undefined4 *)(thisPtr + 0x2c) = 0;
        *(undefined4 *)(thisPtr + 0x28) = 0;
    }
    
    // Try to find a free block of sufficient size
    if (*(uint *)(thisPtr + 0x2c) < size) {
        accumulatedSize = 0;
        do {
            node = *(int **)(thisPtr + 0x14);
            if ((node == (int *)0x0) ||
                ((uint)node[8] < (uint)(*(int *)(thisPtr + 0x20) + *(int *)(thisPtr + 0x28)))) break;
            
            // Check if block is still referenced by any of three possible references
            if ((node[8] == 0) || (ref1 = true, *(char *)(node[8] + 9) == '\0')) {
                ref1 = false;
            }
            if ((node[9] == 0) || (ref2 = true, *(char *)(node[9] + 9) == '\0')) {
                ref2 = false;
            }
            if ((node[10] == 0) || (*(char *)(node[10] + 9) == '\0')) {
                ref3 = false;
            } else {
                ref3 = true;
            }
            
            if (ref1 || ref2 || ref3) {
                // Block still in use, cannot reclaim
                *(int *)(thisPtr + 0x2c) = *(int *)(thisPtr + 0x2c) + accumulatedSize;
                return 0;
            }
            
            // Block is free, remove it from the active list and add to free list
            extraVar = *node;
            *(int *)(thisPtr + 0x14) = extraVar;
            *(undefined4 *)(extraVar + 4) = 0;
            *(int *)(thisPtr + 0x1030) = *(int *)(thisPtr + 0x1030) + -1;
            node[1] = 0;
            *node = *(int *)(thisPtr + 0x10);
            *(int **)(*(int *)(thisPtr + 0x10) + 4) = node;
            *(int *)(thisPtr + 0x1c) = *(int *)(thisPtr + 0x1c) + 1;
            *(int **)(thisPtr + 0x10) = node;
            
            // Remove from the per-pool hash/index list
            if (*(int **)(thisPtr + 0x30 + node[3] * 4) == node) {
                *(int *)(thisPtr + 0x30 + node[3] * 4) = node[0xc];
            } else {
                if (node[0xc] != 0) {
                    *(int *)(node[0xc] + 0x34) = node[0xd];
                }
                *(int *)(node[0xd] + 0x30) = node[0xc];
            }
            accumulatedSize = accumulatedSize + node[0xb];
        } while ((uint)(*(int *)(thisPtr + 0x2c) + accumulatedSize) < size);
        
        if (accumulatedSize != 0) {
            *(int *)(thisPtr + 0x2c) = *(int *)(thisPtr + 0x2c) + (accumulatedSize - size);
        }
    } else {
        *(uint *)(thisPtr + 0x2c) = *(uint *)(thisPtr + 0x2c) - size;
    }
    
    extraVar = *(int *)(thisPtr + 0x28);
    *outOffset = extraVar;
    *(uint *)(thisPtr + 0x28) = extraVar + size;
    return 1;
}