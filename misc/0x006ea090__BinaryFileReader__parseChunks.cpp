// FUNC_NAME: BinaryFileReader::parseChunks
void __thiscall BinaryFileReader::parseChunks(void* thisPtr, undefined4 streamHandle)
{
    char hasMoreData;
    undefined4 chunkType;
    int local_74;
    int local_70;
    int local_6c;
    int local_68;
    
    // open/initialize stream
    openStream(streamHandle);
    // check magic signature  0xa21309a3
    checkMagic(streamHandle, 0xa21309a3);
    
    hasMoreData = checkStreamHasMoreData();
    do {
        if (hasMoreData != '\0') {
            // read vector/quaternion data at offset 0x50
            uint* pData = (uint*)readNextDataPacket();
            *(uint*)((int)thisPtr + 0x50) = pData[0];
            *(uint*)((int)thisPtr + 0x54) = pData[1];
            *(uint*)((int)thisPtr + 0x58) = pData[2];
            *(uint*)((int)thisPtr + 0x5c) = pData[3];
            return;
        }
        skipCurrentData(); // advance stream
        chunkType = getChunkType();
        switch(chunkType) {
        case 0:
            skipCurrentData();
            {
                uint data = readChunkData();
                processChunkType0(data); // e.g., texture or material reference
            }
            break;
        case 1:
            skipCurrentData();
            {
                uint data = readChunkData();
                storeAtOffset70((int)thisPtr + 0x70, data); // e.g., some ID
            }
            break;
        case 2:
            skipCurrentData();
            {
                uint data = readChunkData();
                applyChunkType2(data); // modifies local_74-68 via pointer?
                // Note: local_74..68 are assumed to be set by applyChunkType2 or stack passed by reference
                if (local_74 == -0x45245246) { // 0xBAABADBA
                    if (((local_70 != -0x41104111) || (local_6c != -0x153ea5ab)) || (local_68 != -0x6eeff6ef))
                        goto storeInts;
                }
                else if ((((local_74 != 0) || (local_70 != 0)) || (local_6c != 0)) || (local_68 != 0))
                {
                    storeInts:
                    *(int*)((int)thisPtr + 0x78) = local_74;
                    *(int*)((int)thisPtr + 0x7c) = local_70;
                    *(int*)((int)thisPtr + 0x80) = local_6c;
                    *(int*)((int)thisPtr + 0x84) = local_68;
                }
            }
            break;
        case 3:
            {
                int iVar3 = skipCurrentData(); // returns address of data?
                *(undefined4*)((int)thisPtr + 0x88) = *(undefined4*)(iVar3 + 8);
            }
            break;
        }
        advanceToNextChunk(); // skip to next header
        hasMoreData = checkStreamHasMoreData();
    } while(true);
}