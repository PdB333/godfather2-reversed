// FUNC_NAME: StreamManager::processChunkedStream

// Reconstructed C++ for function at 0x004c5170
// Class: StreamManager (assumed based on offsets and chunking pattern)
// Method: processChunkedStream
// Purpose: Splits a large data buffer into aligned chunks, processes each chunk via FUN_00495510,
//          stores results into an output array. Falls back to single-chunk processing if invalid.

void StreamManager::processChunkedStream(void)
{
    uint chunkIndex;           // local_14?
    int currentPtrOffset;      // iVar2
    int totalSize;             // = *(this + 0x38)
    int currentDataOffset;     // local_1c
    uint chunkSize;            // uVar3
    uint64 chunkOutput[2];     // local_c and local_8 (two 32-bit parts)
    uint64 *chunkOutArray;     // puVar1 starting at this + 0x658

    // +0x654: desired chunk count (max 8)
    *(int *)(this + 0x654) = DAT_01217d04; // some global constant

    totalSize = *(int *)(this + 0x38);             // +0x38: total data size to process
    if ((totalSize > 15) && (*(int *)(this + 0x654) != 0))
    {
        // Clamp chunk count to 8
        if (*(int *)(this + 0x654) > 8)
        {
            *(int *)(this + 0x654) = 8;
        }

        // Align chunk size to 16 bytes (0xfffffff0 mask)
        chunkSize = (totalSize / *(int *)(this + 0x654)) & 0xFFFFFFF0;
        if (chunkSize == 0)
        {
            *(int *)(this + 0x654) = 1;  // fallback to single chunk
        }

        // +0x8 and +0x4: likely width and height or stride parameters
        currentDataOffset = *(int *)(this + 8);
        currentPtrOffset = *(int *)(this + 4);
        chunkIndex = 0;

        // Process all but the last chunk
        int numChunks = *(int *)(this + 0x654);
        if ((numChunks != 1) && (numChunks - 1 >= 0))
        {
            chunkOutArray = (uint64 *)(this + 0x658);
            do
            {
                // FUN_00495510: processes a chunk of data at this + 0x50
                // Parameters:
                //   &chunkOutput (output)
                //   (chunkSize << 24) | (currentDataOffset)?? actually: *(this+0x650) << 24 | chunkSize
                //   this + 0x50 (base data buffer)
                //   currentPtrOffset
                //   currentDataOffset
                //   PTR_LAB_0110a3cc, DAT_0110a3d0 (global callback/data)
                FUN_00495510(&chunkOutput,
                             *(int *)(this + 0x650) << 24 | chunkSize,
                             this + 0x50,
                             currentPtrOffset,
                             currentDataOffset,
                             PTR_LAB_0110a3cc,
                             DAT_0110a3d0);

                currentDataOffset += chunkSize;
                currentPtrOffset += chunkSize * 0x10; // +0x4? stride?
                currentDataOffset += chunkSize;        // +0x8? update

                // Store output into array (two 32-bit values per slot)
                chunkOutArray[1] = chunkOutput[1];
                *chunkOutArray = chunkOutput[0];

                chunkIndex++;
                chunkOutArray += 2; // each slot is 8 bytes (two ints)
            } 
            while (chunkIndex < numChunks - 1);
        }

        // Process the last chunk (remaining size)
        FUN_00495510(&chunkOutput,
                     (*(int *)(this + 0x38) - currentDataOffset) | (*(int *)(this + 0x650) << 24),
                     this + 0x50,
                     currentPtrOffset,
                     currentDataOffset,
                     PTR_LAB_0110a3cc,
                     DAT_0110a3d0);

        int slotIndex = *(int *)(this + 0x654);
        *(uint64 *)(this + 0x650 + slotIndex * 8) = chunkOutput; // store final chunk output at +0x650+(slot*8)
        return;
    }

    // Fallback: process entire buffer as single chunk
    FUN_004d2ba0(this + 0x50, *(int *)(this + 0x650), totalSize);
    return;
}