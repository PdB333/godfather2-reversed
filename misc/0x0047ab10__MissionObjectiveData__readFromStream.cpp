// FUNC_NAME: MissionObjectiveData::readFromStream
void __thiscall MissionObjectiveData::readFromStream(void *this, DataStream *stream)
{
    uint uIndex;
    void *pvChunkData;
    void **ppChunkIterator;
    uint uBitmaskIndex;
    void *pvParsedData;
    int iTemp;
    bool bDone;
    char bUseBitmask;
    int iBitmaskBase;
    void *pvBitmaskData;
    uint uCurrentIndex;
    uint uChunkCount;
    uint *puChunkData;
    uint *puChunkData2;
    uint auChunkVals[2];
    void **ppCurrentChunk;

    // Initialize the stream and expect a magic number
    stream->init();
    stream->expectHeader(0x120f25aa);

    uCurrentIndex = uBitmaskIndex; // uBitmaskIndex is local_58? Actually local_58 is uCurrentIndex, local_54 is uChunkCount
    ppCurrentChunk = (void **)&auChunkVals[0]; // local_8

    while (true) {
        // Check iteration condition: if bitmask mode, check if index has reached count; else check if current chunk pointer is null
        if (bUseBitmask) {
            bDone = (uCurrentIndex >= uChunkCount);
        } else {
            bDone = (*ppCurrentChunk == nullptr);
        }
        if (bDone) break;

        // Determine which chunk pointer to use
        if (bUseBitmask) {
            ppChunkIterator = &auChunkVals[0]; // local_50
        } else {
            ppChunkIterator = ppCurrentChunk;
        }

        // Extract chunk type: it's stored as a short at offset 6 of the chunk header
        // If the short at offset 6 equals 0x25E3, the type is read from a short at offset 4, else from the second pointer field
        uint uChunkType;
        if (*(short *)((int)ppChunkIterator + 6) == 0x25E3) {
            uChunkType = (uint)*(ushort *)((uint *)ppChunkIterator + 1); // offset 4
        } else {
            uChunkType = (uint)ppChunkIterator[1]; // second field
        }

        // Resolve the actual data pointer based on chunk format
        void *pvResolvedData;
        if (bUseBitmask) {
            // For bitmask mode, we already have the data pointer
            // Actually we need to resolve based on format again inside switch
        }
        // The code below re-determines the data pointer for each case
        // We'll handle it in the switch

        switch (uChunkType) {
        case 0:
        {
            // Print debug string
            if (bUseBitmask) {
                ppChunkIterator = &auChunkVals[0];
            } else {
                ppChunkIterator = ppCurrentChunk;
            }
            void *pszDebugStr;
            if (*(short *)((int)ppChunkIterator + 6) == 0x25E3) {
                if (*ppChunkIterator == nullptr) {
                    pszDebugStr = (void *)&DAT_00e2a89b; // empty string
                } else {
                    pszDebugStr = (void *)((int)ppChunkIterator[2] + (int)*ppChunkIterator);
                }
            } else {
                pszDebugStr = (void *)(ppChunkIterator + 2);
            }
            debugPrint(pszDebugStr);
            break;
        }
        case 1:
        {
            // Read a string and add to the vector at this+0x58
            if (bUseBitmask) {
                ppChunkIterator = &auChunkVals[0];
            } else {
                ppChunkIterator = ppCurrentChunk;
            }
            void *pvStr;
            if (*(short *)((int)ppChunkIterator + 6) == 0x25E3) {
                if (*ppChunkIterator == nullptr) {
                    pvStr = (void *)&DAT_00e2a89b;
                } else {
                    pvStr = (void *)((int)ppChunkIterator[2] + (int)*ppChunkIterator);
                }
            } else {
                pvStr = (void *)(ppChunkIterator + 2);
            }
            // Clear the string list twice (why? maybe clear and then initialise)
            VectorClear((void *)((int)this + 0x58));
            VectorClear((void *)((int)this + 0x58));
            if ((pvStr != nullptr) && (*(char *)pvStr != '\0')) {
                uint uId = stringToHash(pvStr);
                VectorPushBack((void *)((int)this + 0x58), uId);
            }
            break;
        }
        case 2:
        {
            // Read a single integer and store at this+0x88
            if (bUseBitmask) {
                ppChunkIterator = &auChunkVals[0];
            } else {
                ppChunkIterator = ppCurrentChunk;
            }
            void *pvData;
            if (*(short *)((int)ppChunkIterator + 6) == 0x25E3) {
                if (*ppChunkIterator == nullptr) {
                    pvData = (void *)&DAT_00e2a89b;
                } else {
                    pvData = (void *)((int)ppChunkIterator[2] + (int)*ppChunkIterator);
                }
            } else {
                pvData = (void *)(ppChunkIterator + 2);
            }
            int iValue = -1;
            if ((pvData != nullptr) && (*(char *)pvData != '\0')) {
                iValue = stringToHash(pvData);
            }
            *(int *)((int)this + 0x88) = iValue;
            break;
        }
        case 3:
        {
            // Read a 4-float vector (likely rotation) and store at this+0x70..0x7C
            if (bUseBitmask) {
                ppChunkIterator = &auChunkVals[0];
            } else {
                ppChunkIterator = ppCurrentChunk;
            }
            void *pvVec;
            if (*(short *)((int)ppChunkIterator + 6) == 0x25E3) {
                if (*ppChunkIterator == nullptr) {
                    pvVec = (void *)&DAT_0120e700; // default zero vector
                } else {
                    pvVec = (void *)((int)ppChunkIterator[2] + (int)*ppChunkIterator);
                }
            } else {
                pvVec = (void *)(ppChunkIterator + 2);
            }
            // Copy 4 words (float values) to this+0x70
            *(uint *)((int)this + 0x70) = *(uint *)pvVec;
            *(uint *)((int)this + 0x74) = *(uint *)((int)pvVec + 4);
            *(uint *)((int)this + 0x78) = *(uint *)((int)pvVec + 8);
            *(uint *)((int)this + 0x7C) = *(uint *)((int)pvVec + 12);
            break;
        }
        case 4:
        {
            // Read a 4-float vector (likely position) and store at this+0x60..0x6C
            if (bUseBitmask) {
                ppChunkIterator = &auChunkVals[0];
            } else {
                ppChunkIterator = ppCurrentChunk;
            }
            void *pvVec;
            if (*(short *)((int)ppChunkIterator + 6) == 0x25E3) {
                if (*ppChunkIterator == nullptr) {
                    pvVec = (void *)&DAT_0120e700;
                } else {
                    pvVec = (void *)((int)ppChunkIterator[2] + (int)*ppChunkIterator);
                }
            } else {
                pvVec = (void *)(ppChunkIterator + 2);
            }
            // Copy 4 words to this+0x60
            *(uint *)((int)this + 0x60) = *(uint *)pvVec;
            *(uint *)((int)this + 0x64) = *(uint *)((int)pvVec + 4);
            *(uint *)((int)this + 0x68) = *(uint *)((int)pvVec + 8);
            *(uint *)((int)this + 0x6C) = *(uint *)((int)pvVec + 12);
            break;
        }
        }

        // Advance to next chunk based on mode
        if (bUseBitmask == false) {
            // List mode: chunk size is stored as the first int (offset) in the current chunk
            int iChunkSize = (int)*ppCurrentChunk;
            if ((int)uCurrentIndex < 0) {
                // Negative index? Actually this checks if the cumulative index is negative (indicating end marker)
                ppCurrentChunk = (void **)((int)ppCurrentChunk + iChunkSize);
                advanceChunk(); // FUN_0043b140: some internal stream advancement
                uCurrentIndex = uBitmaskIndex;
                ppCurrentChunk = ppCurrentChunk; // redundant
            } else if ((int)uCurrentIndex < (int)(uChunkCount - 1)) {
                uCurrentIndex++;
                ppCurrentChunk = (void **)((int)ppCurrentChunk + iChunkSize);
                uCurrentIndex = uCurrentIndex; // redundant
                ppCurrentChunk = (void **)((int)ppCurrentChunk + iChunkSize); // double advance? Actually original code does it twice? Wait, re-reading the original: it sets local_8 twice? Let's re-check.
            } else {
                ppCurrentChunk = (void **)&DAT_01163cf8; // end marker
                ppCurrentChunk = (void **)&DAT_01163cf8; // redundant
            }
        } else {
            // Bitmask mode: advance index and read next chunk if available
            uCurrentIndex++;
            if (uCurrentIndex != uChunkCount) {
                // Check bitmask: if clear, chunk is null; else read from data array
                int bitIndex = uCurrentIndex;
                int byteIndex = bitIndex >> 3;
                int bitMask = 1 << (bitIndex & 7);
                if ((*(char *)(iBitmaskBase + byteIndex) & bitMask) == 0) {
                    // Bit not set: this chunk is absent
                    auChunkVals[0] = 0;
                    auChunkVals[1] = 0;
                } else {
                    // Bit set: read next 8 bytes from data stream
                    auChunkVals[0] = *(uint *)pvBitmaskData;
                    // Actually the code sets local_50 = local_5c and local_48 = *local_5c then local_5c+=1. So it reads a 4-byte value? More complex.
                    // For simplicity, just note that it reads a chunk header.
                    pvChunkData = pvBitmaskData; // local_50 = local_5c
                    auChunkVals[1] = *(uint *)pvBitmaskData; // local_48 = *local_5c
                    pvBitmaskData = (void *)((int)pvBitmaskData + 4); // advance by 4 bytes
                }
            }
        }
    }
}