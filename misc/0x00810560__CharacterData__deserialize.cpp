// FUNC_NAME: CharacterData::deserialize
void __thiscall CharacterData::deserialize(int thisPtr, int streamPtr) {
    // Open binary stream for reading
    streamOpen(streamPtr);
    // Begin main chunk with magic identifier 0xb390b11a
    streamBeginChunk(streamPtr, 0xb390b11a);
    streamSetVersion(1);
    // Check if stream is in error state (e.g., missing chunk)
    if (!streamIsError(streamPtr)) {
        // Prepare temporary buffer for 4x3 transformation matrix (12 floats = 48 bytes)
        // local_120, local_110, local_100, local_f0: low 8 bytes of each row
        // local_118, local_108, local_f8, local_e8: high 4 bytes of each row
        unsigned long long row0Low = 0, row1Low = 0, row2Low = 0, row3Low = 0;
        int row0High = 0, row1High = 0, row2High = 0, row3High = _DAT_00d5780c; // global default

        // Read matrix data from stream (two-step: advance buffer pointer, then read block)
        streamReadBuffer(streamPtr);
        streamReadBlock(streamPtr, &row0Low);
        streamReadBlock(streamPtr, &row0High);
        streamReadBlock(streamPtr, &row1Low);
        streamReadBlock(streamPtr, &row1High);
        streamReadBlock(streamPtr, &row2Low);
        streamReadBlock(streamPtr, &row2High);
        streamReadBlock(streamPtr, &row3Low);
        streamReadBlock(streamPtr, &row3High);

        // Transfer row data to object fields (offset +0x90..+0xd8)
        *(unsigned long long*)(thisPtr + 0xd0) = row3Low;   // +0xd0: row3 low
        *(unsigned long long*)(thisPtr + 0xa0) = row1Low;   // +0xa0: row1 low
        *(unsigned long long*)(thisPtr + 0x90) = row0Low;   // +0x90: row0 low
        *(int*)(thisPtr + 0xd8) = row3High;                // +0xd8: row3 high
        *(int*)(thisPtr + 0xa8) = row1High;                // +0xa8: row1 high
        *(unsigned long long*)(thisPtr + 0xb0) = row2Low;   // +0xb0: row2 low
        *(int*)(thisPtr + 0x98) = row0High;                // +0x98: row0 high
        *(int*)(thisPtr + 0xb8) = row2High;                // +0xb8: row2 high

        // Apply internal matrix copy/initialization (likely aligns rows)
        matrixApply((void*)(thisPtr + 0x90), (void*)(thisPtr + 0x90));
    }

    // Begin second chunk with magic 0x4b590617 (contains optional sub-chunks)
    streamBeginChunk(streamPtr, 0x4b590617);
    // Loop reading sub-chunks until stream ends or error
    while (true) {
        if (streamIsError(streamPtr)) {
            return;
        }
        streamReadBuffer(streamPtr);
        int chunkType = streamReadChunkType(streamPtr);
        switch (chunkType) {
        case 0: {
            // Read and set field at +0x74
            streamReadBuffer(streamPtr);
            int value = streamReadValue(streamPtr);
            setField74(thisPtr + 0x74, value); // +0x74: e.g., walkSpeed
            break;
        }
        case 1: {
            // Read and set field at +0x7C
            streamReadBuffer(streamPtr);
            int value = streamReadValue(streamPtr);
            setField7C(thisPtr + 0x7C, value); // +0x7C: e.g., runSpeed
            break;
        }
        case 2: {
            // Read sub-object at +0x64 (decimal 100)
            int subObjPtr = thisPtr + 100;
            streamReadBuffer(subObjPtr);
            streamReadSubObject(subObjPtr); // +0x64: sub-object (e.g., inventory)
            break;
        }
        case 3: {
            // Read sub-object at +0x54
            int subObjPtr = thisPtr + 0x54;
            streamReadBuffer(subObjPtr);
            streamReadSubObject(subObjPtr); // +0x54: sub-object (e.g., skills)
            break;
        }
        case 4: {
            // Read value from buffer offset 8 and store at +0xDC
            int bufPtr = streamReadBuffer(streamPtr);
            *(int*)(thisPtr + 0xDC) = *(int*)(bufPtr + 8); // +0xDC: e.g., health
            break;
        }
        case 5: {
            // Read value from buffer offset 8 and store at +0xE0
            int bufPtr = streamReadBuffer(streamPtr);
            *(int*)(thisPtr + 0xE0) = *(int*)(bufPtr + 8); // +0xE0: e.g., stamina
            break;
        }
        }
        streamSkipChunk(streamPtr);
    }
}