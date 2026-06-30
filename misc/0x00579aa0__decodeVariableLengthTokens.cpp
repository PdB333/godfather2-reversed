// FUNC_NAME: decodeVariableLengthTokens
// Function address: 0x00579aa0
// Decompresses a stream of variable-length tokens from a compressed buffer.
// The stream format is a custom EA EARS compression, used for network packets.
// Parameter pStreamPtr: pointer to current read position (updated on return)
// Parameter remainingCount: number of tokens to decode (passed in EAX)
void decodeVariableLengthTokens(int* pStreamPtr, int remainingCount)
{
    // External tables for token size and base offset, indexed by token type (0-15)
    extern int tokenSizeTable[16];   // DAT_00e2c758
    extern int tokenBaseTable[16];   // DAT_00e2c720

    byte* currentPtr = (byte*)*pStreamPtr;
    byte headerByte = *currentPtr;
    byte lowNibble = headerByte & 0xF;
    
    if (lowNibble == 5)
    {
        // Type 5: Multiple tokens encoded with counts
        uint numTokens = (uint)(currentPtr[1] << 4) | (uint)(headerByte >> 4);
        // Calculate base pointer (relative offset from header)
        uint offset = *(ushort*)(currentPtr + 2);
        byte* basePtr = currentPtr + 2 + (offset - 2); // equivalent to currentPtr + offset
        currentPtr += 4; // Skip header (1+1+2 bytes)
        
        if (numTokens != 0)
        {
            do
            {
                uint tokenLength = (uint)(currentPtr[1] << 4) | (uint)(*currentPtr >> 4);
                int lenMinusOne = tokenLength - 1;
                numTokens--;
                uint tokenType = *currentPtr & 0xF;
                
                if (remainingCount < lenMinusOne)
                {
                    // Not enough tokens left, flush or signal
                    switch (tokenType)
                    {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 6:
                    case 7:
                    case 0xD:
                        *pStreamPtr = (int)basePtr;
                        return;
                    case 4:
                        // Pops two entries from a stack (FUN_00579a20)
                        FUN_00579a20();
                        FUN_00579a20();
                        break;
                    }
                    *pStreamPtr = (int)basePtr;
                    return;
                }
                
                remainingCount -= lenMinusOne;
                // Advance current pointer by token size
                currentPtr += tokenSizeTable[tokenType] * tokenLength + tokenBaseTable[tokenType];
            } while ((int)numTokens > 0);
            
            *pStreamPtr = (int)currentPtr;
            return;
        }
    }
    else
    {
        // Non-type-5: simple short tokens
        switch (lowNibble)
        {
        case 0:
            *pStreamPtr = (int)(currentPtr + 5);
            return;
        case 1:
            *pStreamPtr = (int)(currentPtr + 8);
            return;
        case 2:
            *pStreamPtr = (int)(currentPtr + 0xB);
            return;
        case 3:
            *pStreamPtr = (int)(currentPtr + 0xE);
            return;
        case 4:
        {
            byte b = currentPtr[1];
            FUN_00579a20();
            FUN_00579a20();
            uint count = (uint)(b << 4) | (uint)(headerByte >> 4);
            *pStreamPtr = (int)(currentPtr + 2 + count * 4);
            return;
        }
        case 6:
        {
            uint count = (uint)(currentPtr[1] << 4) | (uint)(headerByte >> 4);
            *pStreamPtr = (int)(currentPtr + 8 + count);
            return;
        }
        case 7:
        {
            uint count = (uint)(currentPtr[1] << 4) | (uint)(headerByte >> 4);
            *pStreamPtr = (int)(currentPtr + 8 + count * 2);
            return;
        }
        case 0xC:
            currentPtr += 2;
            break;
        case 0xD:
            *pStreamPtr = (int)(currentPtr + 2);
            return;
        }
    }
    
    *pStreamPtr = (int)currentPtr;
    return;
}