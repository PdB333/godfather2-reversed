// FUNC_NAME: PacketParser::parseChunks
int __fastcall parseChunks(undefined4 param_1, int *pBuffer, int *pOutChunkData, int *pOutChunkSize, undefined4 *pOutChunkType)
{
    int savedOffset;
    int *pCurrent;
    int chunkFound;
    int chunkDataOffset;
    undefined4 chunkHeader;
    undefined4 chunkType;
    undefined4 chunkSize;
    int chunkData;
    
    savedOffset = pBuffer[4]; // +0x10 offset in buffer struct
    pCurrent = (int *)*pBuffer; // +0x00 - pointer to raw data
    chunkFound = 0;
    pBuffer[4] = 0; // reset offset
    chunkDataOffset = *pCurrent; // read first 4 bytes
    pBuffer[4] = 4; // advance offset by 4
    
    // Check for magic number "Fxap" (0x61707866)
    if (chunkDataOffset != 0x61707866) {
        return 0;
    }
    
    *pOutChunkData = 0;
    pBuffer[4] = 0; // reset offset again
    chunkData = 0;
    
    // Parse chunks until end of buffer (with 8 byte safety margin)
    if (pBuffer[3] != 8 && pBuffer[3] + -8 >= 0) {
        do {
            if (chunkFound != 0) break;
            
            chunkDataOffset = pBuffer[4];
            // Read 4-byte chunk header (big-endian)
            chunkHeader = CONCAT13(*(undefined1 *)((int)pCurrent + chunkDataOffset + 3),
                                  CONCAT12(*(undefined1 *)((int)pCurrent + chunkDataOffset + 2),
                                           CONCAT11(*(undefined1 *)((int)pCurrent + chunkDataOffset + 1),
                                                    *(undefined1 *)((int)pCurrent + chunkDataOffset))));
            pBuffer[4] = chunkDataOffset + 4;
            
            if (chunkHeader == 0x61707866) { // "Fxap" - another header
                chunkDataOffset = chunkDataOffset + 8;
                pBuffer[4] = chunkDataOffset;
            }
            else if (chunkHeader == 0x74783468) { // "hx4t" - texture chunk
                *pOutChunkType = 1;
                // Read 4-byte chunk size (big-endian)
                chunkType = CONCAT13(*(undefined1 *)(chunkDataOffset + 7 + (int)pCurrent),
                                    CONCAT12(*(undefined1 *)(chunkDataOffset + 6 + (int)pCurrent),
                                             CONCAT11(*(undefined1 *)(chunkDataOffset + 5 + (int)pCurrent),
                                                      *(undefined1 *)(chunkDataOffset + 4 + (int)pCurrent))));
                chunkData = chunkType + -8;
                chunkFound = chunkDataOffset + 8 + (int)pCurrent;
                pBuffer[4] = chunkDataOffset + 8;
                if (chunkFound != 0) {
                    *pOutChunkData = chunkDataOffset;
                }
            }
            else if (chunkHeader == 0x616c6967) { // "gila" - ??? 
                *pOutChunkData = chunkDataOffset;
            }
            
            pBuffer[4] = chunkDataOffset + 4;
            // Read chunk size (big-endian)
            chunkSize = CONCAT13(*(undefined1 *)(chunkDataOffset + 7 + (int)pCurrent),
                                CONCAT12(*(undefined1 *)(chunkDataOffset + 6 + (int)pCurrent),
                                         CONCAT11(*(undefined1 *)(chunkDataOffset + 5 + (int)pCurrent),
                                                  *(undefined1 *)(chunkDataOffset + 4 + (int)pCurrent))));
            pBuffer[4] = chunkSize + chunkDataOffset;
        } while (pBuffer[4] < pBuffer[3] + -8);
    }
    
    pBuffer[4] = savedOffset; // restore original offset
    *pOutChunkSize = chunkData;
    return chunkFound;
}