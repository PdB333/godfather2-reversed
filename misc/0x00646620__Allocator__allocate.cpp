// FUNC_NAME: Allocator::allocate
// Purpose: Core memory allocation routine for EARS heap/pool allocator.
// Manages multiple free lists based on block size, supports splitting, coalescing,
// and fallback to system heap. Thread-safe via critical section.
// Param1 (this) : Allocator object
// Param2 (hint) : Unused alignment hint?
// Param3 (flags): Bitfield controlling allocation behavior
//   Bit0 (1):  "allowSmall" – use small block lists
//   Bit3 (8):  "forceSystem" – directly allocate from OS
//   Bit9 (0x200): "useLarge" – use large block search
//   Bit30 (0x40000000): "retry" – flag for retry with adjusted alignment

void* __thiscall Allocator::allocate(int hint, uint flags)
{
    uint local_18 = 0;
    uint local_8 = 0;
    void* result = nullptr;

    // If force system allocation, jump to system allocator directly
    if ((flags & 8) != 0)
    {
        return systemAlloc();
    }

    // Obtain the request size after rounding (e.g., aligned to 8 bytes)
    uint requestSize = roundUpSize();

    // Main allocation loop; flags may be modified on retry
    while (true)
    {
        bool allowSmall = (flags & 1) != 0;
        bool useLarge = (flags & 0x200) != 0;

        // ---- Fast path: small blocks (size < 0x200) stored in separate lists ----
        if (!useLarge)
        {
            // Check if a small block of exact size exists in the direct bucket array (index = size>>3)
            if (requestSize <= *(uint*)(this + 4) && !allowSmall)
            {
                int* bucketHead = (int*)(this + (requestSize >> 3) * 4);
                int blockPtr = *bucketHead;
                if (blockPtr != 0)
                {
                    // Mark block as used (clear ownership bits)
                    *(uint*)(blockPtr + 4) &= 0x7ffffffb;
                    *bucketHead = *(int*)(blockPtr + 0xc); // remove from list
                    return (void*)(blockPtr + 8);
                }
            }

            // ---- Small block: try exact fit in size-class free list ----
            if (requestSize < 0x200)
            {
                local_18 = requestSize >> 3;
                uint listHeadAddr = this + 0x28 + local_18 * 8;
                uint blockAddr = *(uint*)(listHeadAddr + 8);
                if (blockAddr != listHeadAddr)
                {
                    uint lastBlockBoundary = *(uint*)(this + 0x468);
                    if (lastBlockBoundary != 0)
                    {
                        bool boundaryOK;
                        if (!allowSmall)
                            boundaryOK = (blockAddr < lastBlockBoundary);
                        else
                            boundaryOK = (lastBlockBoundary <= (blockAddr + requestSize));
                        if (!boundaryOK)
                            goto LAB_00646765; // skip, try larger
                    }
                    // Remove block from free list, mark as used
                    uint* flagsPtr = (uint*)(blockAddr + 4 + requestSize);
                    *flagsPtr |= 1; // mark next block as used? (sentinel)
                    *(uint*)(*(int*)(blockAddr + 8) + 0xc) = *(uint*)(blockAddr + 0xc);
                    *(uint*)(*(int*)(blockAddr + 0xc) + 8) = *(uint*)(blockAddr + 8);
                    return (void*)(blockAddr + 8);
                }
            }
            // ---- Larger small blocks: determine size class index (log2 bins) ----
            else
            {
                if (requestSize >> 6 < 0x21)
                    local_18 = (requestSize >> 6) + 0x38;
                else if (requestSize >> 9 < 0x15)
                    local_18 = (requestSize >> 9) + 0x5b;
                else if (requestSize >> 0xc < 0xb)
                    local_18 = (requestSize >> 0xc) + 0x6e;
                else if (requestSize >> 0xf < 5)
                    local_18 = (requestSize >> 0xf) + 0x77;
                else if (requestSize >> 0x12 < 3)
                    local_18 = (requestSize >> 0x12) + 0x7c;
                else
                    local_18 = 0x7e;

                // If the "small available" flag is set, coalesce first
                if ((*(uint*)(this + 4) & 1) != 0)
                    coalesce();
            }
        }

        // ---- LAB_00646765: Search all free lists for a suitable block ----
        LAB_00646765:
        while (true)
        {
            // ---- If not using large flag, walk the primary free list ----
            if (!useLarge)
            {
                // Walk the main free list rooted at this + 0x30 (list pointer at +0x38)
                uint listHead = this + 0x30;
                uint currentBlock = *(uint*)(this + 0x38);
                while (currentBlock != listHead)
                {
                    uint lastBlockBoundary = *(uint*)(this + 0x468);
                    uint blockSize = *(uint*)(currentBlock + 4) & 0x7ffffff8;
                    bool boundaryOK;
                    if (lastBlockBoundary == 0)
                        boundaryOK = true;
                    else if (!allowSmall)
                        boundaryOK = (currentBlock < lastBlockBoundary);
                    else
                        boundaryOK = (lastBlockBoundary <= (blockSize + currentBlock));

                    // Special case: this block is the "reserved" block at 0x444
                    uint nextBlockPtr = *(uint*)(currentBlock + 8);
                    if ((requestSize < 0x200) && (currentBlock == *(uint*)(this + 0x444)) && (nextBlockPtr == listHead))
                    {
                        if ((requestSize + 0x10 < blockSize) && boundaryOK)
                        {
                            removeFreeBlock(currentBlock);
                            return (void*)(currentBlock + 8);
                        }
                    }

                    // Update list head for iteration
                    *(uint*)(this + 0x38) = nextBlockPtr;
                    *(uint*)(nextBlockPtr + 0xc) = listHead;

                    // Exact size match?
                    if ((blockSize == requestSize) && boundaryOK)
                    {
                        uint* flagsPtr = (uint*)(blockSize + 4 + currentBlock);
                        *flagsPtr |= 1;
                        return (void*)(currentBlock + 8);
                    }

                    // Insert current block back into appropriate free list (rehash)
                    insertFreeBlock(currentBlock);
                    currentBlock = *(uint*)(this + 0x38);
                }

                // ---- Not in main list: search size-class buckets ----
                if (requestSize >= 0x200)
                {
                    uint bucketIndex = local_18;
                    // Walk the bucket at base + 0x28 + bucketIndex*8
                    uint bucketHead = this + 0x28 + bucketIndex * 8;
                    uint blockAddr = *(uint*)(bucketHead + 8); // first block
                    while (blockAddr != bucketHead)
                    {
                        uint blockSize = *(uint*)(blockAddr + 4) & 0x7ffffff8;
                        if (requestSize <= blockSize)
                        {
                            uint lastBlockBoundary = *(uint*)(this + 0x468);
                            bool boundaryOK;
                            if (lastBlockBoundary == 0)
                                goto LAB_00646b76;
                            if (!allowSmall)
                                boundaryOK = (blockAddr < lastBlockBoundary);
                            else
                                boundaryOK = (lastBlockBoundary <= (blockSize + blockAddr));
                            if (boundaryOK)
                            {
                                LAB_00646b76:
                                removeFreeBlock(blockAddr);
                                return (void*)(blockAddr + 8);
                            }
                        }
                        blockAddr = *(uint*)(blockAddr + 8);
                    }
                }

                // Advance bucket index
                local_18++;
                uint bitMapAddrBase = this + 0x430;
                uint wordIndex = local_18 >> 5;
                uint bitmapWord = *(uint*)(bitMapAddrBase + wordIndex * 4);
                uint bitMask = 1 << (local_18 & 0x1f);

                // ---- Walk bitmap to find next nonempty bucket ----
                while (true)
                {
                    // If bitMask wraps around or bitmap word lower than mask, skip to next word
                    if ((bitmapWord < bitMask) || (bitMask == 0))
                    {
                        // Move to next bitmap word
                        wordIndex++;
                        if (wordIndex > 3) // only 4 words (128 bits)
                            goto LAB_00646959; // all buckets empty
                        bitmapWord = *(uint*)(bitMapAddrBase + wordIndex * 4);
                        if (bitmapWord == 0)
                            continue;
                        // Reset base address for this word
                        uint newBucketAddr = this + 0x28 + wordIndex * 0x100;
                        bitMask = 1;
                    }

                    // Scan bits to find set bit (free bucket)
                    while ((bitmapWord & bitMask) == 0)
                    {
                        bitMask <<= 1;
                        newBucketAddr += 8;
                    }

                    uint bucketAddr = newBucketAddr;
                    uint blockAddr = *(uint*)(bucketAddr + 8);
                    if (blockAddr != bucketAddr)
                        break; // found a nonempty bucket

                    // Bucket was empty despite bitmap bit set? Clear and continue
                    bitmapWord &= ~bitMask;
                    *(uint*)(bitMapAddrBase + wordIndex * 4) = bitmapWord;
                    newBucketAddr += 8;
                    bitMask <<= 1;
                }

                // Found a nonempty bucket; walk its list
                while (true)
                {
                    uint blockSize = *(uint*)(blockAddr + 4);
                    uint lastBlockBoundary = *(uint*)(this + 0x468);
                    do {
                        if (lastBlockBoundary == 0)
                        {
                            LAB_0064693f:
                            if (blockAddr != bucketAddr)
                            {
                                removeFreeBlock(blockAddr);
                                return (void*)(blockAddr + 8);
                            }
                            // Bucket empty; advance
                            bucketAddr += 8;
                            bitMask <<= 1;
                            goto LAB_00646880; // restart bitmap scan
                        }
                        bool boundaryOK;
                        if (!allowSmall)
                            boundaryOK = (blockAddr < lastBlockBoundary);
                        else
                            boundaryOK = (lastBlockBoundary <= ((blockSize & 0x7ffffff8) + blockAddr));
                        if (boundaryOK)
                            goto LAB_0064693f;
                        blockAddr = *(uint*)(blockAddr + 8);
                        blockSize = *(uint*)(blockAddr + 4);
                    } while (blockAddr != bucketAddr);
                    bucketAddr += 8;
                    bitMask <<= 1;
                }
                // End of bitmap walk
                LAB_00646880:; // continue outer loop
            }

            // ---- LAB_00646959: Try to split the "last block" (largest) ----
            uint lastBlockAddr = *(uint*)(this + 0x440);
            uint lastBlockSize = *(uint*)(lastBlockAddr + 4) & 0x7ffffff8;
            if (requestSize + 0x10 <= lastBlockSize)
            {
                uint newBlockAddr;
                if (!allowSmall)
                {
                    // Split from the beginning
                    uint remainderSize = lastBlockSize - requestSize;
                    *(uint*)(lastBlockAddr + 4) = requestSize | 1;
                    newBlockAddr = lastBlockAddr + requestSize;
                    *(uint*)(newBlockAddr + 4) = remainderSize | 1;
                    // The prev pointer at newBlockAddr + 0??? Not needed here
                }
                else
                {
                    // Split from the end (allowSmall flag)
                    uint newBlockAddr = (lastBlockAddr - requestSize) + lastBlockSize;
                    // Check alignment
                    if ((newBlockAddr & 7) == 0)
                    {
                        uint remainderSize = lastBlockSize - requestSize;
                        *(uint*)(newBlockAddr + 4) = requestSize;
                        uint* flagsPtr = (uint*)(newBlockAddr + 4 + requestSize);
                        *flagsPtr |= 1;
                        *(uint*)(newBlockAddr + requestSize) = requestSize;
                    }
                    else
                    {
                        // Align down to 8 bytes
                        newBlockAddr &= 0xfffffff8;
                        uint remainderSize = newBlockAddr - lastBlockAddr;
                        uint blockSize = lastBlockSize - remainderSize;
                        *(uint*)(newBlockAddr + 4) = blockSize;
                        uint* flagsPtr = (uint*)(newBlockAddr + 4 + blockSize);
                        *flagsPtr |= 1;
                        *(uint*)(newBlockAddr + blockSize) = blockSize;
                    }
                }
                // Update last block pointer and set up new block metadata
                *(uint*)(this + 0x440) = newBlockAddr;
                *(uint*)(newBlockAddr + 0xc) = newBlockAddr; // prev?
                *(uint*)(newBlockAddr + 8) = newBlockAddr; // next? (self-referencing)
                *(uint*)(newBlockAddr + 4) = remainderSize | 1;
                *(uint*)(remainderSize + newBlockAddr) = remainderSize;

                // Update "lastBlockBoundary" if not disabled
                if (*(char*)(this + 0x46c) == '\0')
                {
                    *(uint*)(this + 0x468) = (*(uint*)(*(int*)(this + 0x440) + 4) >> 1 & 0x3ffffffc) + *(int*)(this + 0x440);
                }
                return (void*)(newBlockAddr + 8);
            }

            // ---- Cannot split; if coalescing flag is set, coalesce and retry ----
            if ((*(byte*)(this + 4) & 1) == 0)
                break; // no coalescing, exit loop

            coalesce();
            local_18 = requestSize >> 3;
        }

        // ---- If we reach here, allocation failed in the main heap ----
        // Try larger system page allocation if allowed
        if (!useLarge)
        {
            // Check if we can allocate from system heap (if flag set and not exhausted)
            if ((*(char*)(this + 0x46d) != '\0') && (*(uint*)(this + 0x494) <= requestSize) &&
                (*(int*)(this + 0x488) < *(int*)(this + 0x490)))
            {
                result = systemAlloc();
                if (result != nullptr)
                    return result;
            }

            // If retry flag not set, set it and loop with adjusted alignment
            if ((flags & 0x40000000) == 0 && *(char*)(this + 0x46c) == '\0')
            {
                if (!allowSmall)
                    flags = flags | 0x40000001;
                else
                    flags = (flags & 0xfffffffc) | 0x40000000;
                local_18 = 0;
                local_8 = 0;
                result = nullptr;
                if ((flags & 8) != 0)
                    return systemAlloc(); // force system alloc
                continue; // retry
            }

            // ---- Try large block allocation from large pool ----
            if (*(char*)(this + 0x46d) != '\0')
            {
                void* largeBlock = largeAlloc(requestSize);
                if (largeBlock != nullptr)
                {
                    uint* flagsPtr = (uint*)((*(uint*)(largeBlock + 4) & 0x7ffffff8) + 4 + largeBlock);
                    *flagsPtr |= 1;
                    return (void*)(largeBlock + 8);
                }
            }
            if (result != nullptr)
                return result;

            // Check if we should retry via callback
            if (*(int*)(this + 0x4ac) == 0)
                return nullptr; // no callback -> out of memory

            local_8++;
            if (*(uint*)(this + 0x4b4) <= local_8)
                return nullptr; // max retries exceeded

            // Callback to free memory (e.g., coalesce or OS call)
            // Leave critical section before callback, re-enter after
            uint* critSecPtr = *(uint**)(this + 0x4e8);
            if (critSecPtr != nullptr)
            {
                int lockCount = *(int*)(critSecPtr + 0x18);
                if (lockCount > 0)
                {
                    for (int i = 0; i < lockCount; i++)
                    {
                        CRITICAL_SECTION* cs = (CRITICAL_SECTION*)critSecPtr;
                        LeaveCriticalSection(cs);
                        // The counter decrement is implicit? Actually the code decrements iVar16, but we handle differently
                    }
                }
            }

            char callbackResult = (*(char(__thiscall**)(int, int, int))(this + 0x4ac))(this, hint, hint + 0x40, *(int*)(this + 0x4b0));
            // Re-enter critical sections
            if (critSecPtr != nullptr && lockCount > 0)
            {
                for (int i = 0; i < lockCount; i++)
                {
                    CRITICAL_SECTION* cs = (CRITICAL_SECTION*)critSecPtr;
                    EnterCriticalSection(cs);
                }
            }

            if (callbackResult == '\0')
                return nullptr;

            // Callback succeeded, loop again to retry allocation
            // flags unchanged except useLarge flag cleared?
        }
        else
        {
            // useLarge flag was set, clear it and retry
            flags &= 0xfffffdff; // clear bit9
        }
    }
}