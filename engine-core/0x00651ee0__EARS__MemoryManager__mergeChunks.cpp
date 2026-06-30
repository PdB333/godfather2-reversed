// FUNC_NAME: EARS::MemoryManager::mergeChunks
void __thiscall EARS::MemoryManager::mergeChunks(
    int chunkWordCount,     // param_1: number of 4-byte words per chunk (element count)
    void* destPtr,          // param_2: destination or secondary pointer
    uint totalWordCount,    // param_3: total number of 4-byte words
    void* extraParam,       // param_4: extra parameter passed to subroutines
    void* extraParam2,      // param_5: unused?
    void* extraParam3,      // param_6: unused?
    void* tempBuffer        // param_7: temporary buffer to free if non-null
)
{
    int thisPtr = reinterpret_cast<int>(this);  // in_EAX used as base pointer
    uint scratchPad[4];                        // local_1c (4 bytes), but declared as array for alignment
    int internalBuffer = 0;                    // local_18
    int stackBackup = 0;                       // local_8
    uint loopFlags = 0;                        // local_20

    // Process pairs of chunks while at least 2*chunkWordCount elements remain
    while (chunkWordCount * 2 <= static_cast<int>(totalWordCount))
    {
        loopFlags &= 0xffffff00;  // Clear low byte (likely flags or alignment)

        int chunkSizeBytes = chunkWordCount * 4;                     // chunk in bytes
        int firstChunkPtr = thisPtr + chunkWordCount;               // param_3 in call: iVar2 + chunkWordCount*4? Actually iVar1 = iVar2 + chunkWordCount*4
        // Wait: the original code: iVar1 = iVar2 + param_1 * 4;  so firstChunkPtr = thisPtr + chunkWordCount*4
        // But we declared chunkWordCount as number of words, so chunkWordCount*4 gives byte offset.
        // However the original param_1 is the number of 4-byte words? The multiplication by 4 suggests it's already word count.
        // So firstChunkPtr = thisPtr + chunkWordCount * 4;
        // Then nextPtr = firstChunkPtr + chunkWordCount * 4;

        // Recompute accurately:
        int offsetToFirst = chunkWordCount * 4;          // bytes per chunk
        int firstChunkAddr = thisPtr + offsetToFirst;    // iVar1
        int secondChunkAddr = firstChunkAddr + offsetToFirst; // in_EAX

        // Main merge operation – actual merging of two chunks
        FUN_00652640(
            &scratchPad[0],        // local_1c buffer
            thisPtr,               // iVar2 (source start)
            firstChunkAddr,        // iVar1 (first chunk)
            firstChunkAddr,        // duplicate? maybe alignment
            secondChunkAddr,       // in_EAX (second chunk)
            extraParam,            // param_4
            totalWordCount,        // param_3
            loopFlags,             // param_8
            0, 0, 0, 0, 0,        // zeros
            stackBackup            // in_stack_00000028
        );
        stackBackup = local_8;     // save returned stack parameter

        if (internalBuffer != 0)
        {
            FUN_009c8eb0(internalBuffer);  // Free internal temporary buffer
        }

        // Reduce remaining element count by two chunks
        totalWordCount = totalWordCount + chunkWordCount * -2;  // decrement by 2*chunkWordCount

        // Advance base pointer to the end of processed area
        thisPtr = secondChunkAddr;
    }

    // Handle remaining elements (less than 2 chunks)
    if (chunkWordCount < static_cast<int>(totalWordCount))
    {
        // More than one chunk remains, but not enough for a full pair
        int partialStart = thisPtr + chunkWordCount * 4;  // start of the single leftover chunk
        FUN_006524b0(
            thisPtr,               // source start
            partialStart,          // source end?
            partialStart,          // duplicate
            destPtr,               // param_2
            extraParam,            // param_4
            0, 0, 0, 0, 0,        // zeros
            stackBackup            // in_stack
        );
    }
    else
    {
        // At most one chunk – use a simpler processor
        totalWordCount = totalWordCount & 0xffffff00;  // zero out low byte (alignment)
        FUN_00652100(
            &scratchPad[0],        // local_1c
            destPtr,               // param_2
            0, 0, 0, 0, 0,        // zeros
            stackBackup,           // in_stack
            totalWordCount,        // param_9
            totalWordCount,        // param_10 duplicate?
            totalWordCount         // param_11 duplicate?
        );
    }

    // Cleanup internal buffer if allocated during processing
    if (internalBuffer != 0)
    {
        FUN_009c8eb0(internalBuffer);
    }

    // Free provided external temporary buffer
    if (tempBuffer != nullptr)
    {
        FUN_009c8eb0(tempBuffer);
    }
}