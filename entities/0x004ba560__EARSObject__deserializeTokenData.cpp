// FUNC_NAME: EARSObject::deserializeTokenData
void __thiscall EARSObject::deserializeTokenData(void* pStream)
{
    // Call stream setup functions with magic constant
    streamBeginRead(pStream);
    streamReadHeader(pStream, 0x77a210a2);

    // Local variables for parsing
    bool bIsSparse = false; // local_64 (char)
    void** ppCurrentToken = nullptr; // local_8
    void* pTokenBuffer = nullptr; // local_5c
    uint32_t tokenIndex = 0; // local_58
    uint32_t tokenCount = 0; // local_54
    uint32_t tokenDword = 0; // local_48 (unused in switch but set)
    uint16_t tokenShort = 0; // local_4c
    uint8_t* bitmaskBase = nullptr; // local_60

    // Global scale factor (multiplier for field at +0x190)
    float globalScaleFactor = *(float*)0x00e3ac58;

    while (true)
    {
        bool bContinue;
        if (bIsSparse) {
            bContinue = (tokenIndex == tokenCount);
        } else {
            bContinue = (*ppCurrentToken == nullptr);
        }
        if (bContinue) break;

        // Determine pointer to current token record
        void** ppTokenRecord = &tokenDword;
        if (!bIsSparse) {
            ppTokenRecord = ppCurrentToken;
        }

        // Read token type (either from short or from pointer array)
        uint32_t tokenType;
        if (*(int16_t*)((intptr_t)ppTokenRecord + 6) == 0x25e3) {
            tokenType = (uint32_t)*(uint16_t*)(ppTokenRecord + 1);
        } else {
            tokenType = (uint32_t)ppTokenRecord[1];
        }

        // Apply token based on type
        switch (tokenType) {
        case 0:
        {
            // Set byte field at +0x19e (flag1)
            void** pRec = bIsSparse ? &tokenDword : ppCurrentToken;
            *(uint8_t*)((intptr_t)this + 0x19e) = *(uint8_t*)((intptr_t)pRec + 8);
            break;
        }
        case 2:
        {
            // Set byte field at +0x19f (flag2)
            void** pRec = bIsSparse ? &tokenDword : ppCurrentToken;
            *(uint8_t*)((intptr_t)this + 0x19f) = *(uint8_t*)((intptr_t)pRec + 8);
            break;
        }
        case 3:
        {
            // Set byte field at +0x1a0 (flag3)
            void** pRec = bIsSparse ? &tokenDword : ppCurrentToken;
            *(uint8_t*)((intptr_t)this + 0x1a0) = *(uint8_t*)((intptr_t)pRec + 8);
            break;
        }
        case 4:
        {
            // Set float field at +0x1b0, clamped by maxValue * scaleFactor
            void** pRec = bIsSparse ? &tokenDword : ppCurrentToken;
            uint32_t rawValue = (uint32_t)pRec[2];
            float maxValue = *(float*)((intptr_t)this + 0x190);
            float clamped = maxValue * globalScaleFactor;
            if ((float)rawValue > clamped) {
                *(float*)((intptr_t)this + 0x1b0) = clamped;
            } else {
                *(float*)((intptr_t)this + 0x1b0) = (float)rawValue;
            }
            break;
        }
        case 5:
        {
            // Set pointer field at +0x1a8
            void** pRec = bIsSparse ? &tokenDword : ppCurrentToken;
            *(uintptr_t*)((intptr_t)this + 0x1a8) = (uintptr_t)pRec[2];
            break;
        }
        case 6:
        {
            // Set flags field at +0x1ac (bitmask, later ORed)
            void** pRec = bIsSparse ? &tokenDword : ppCurrentToken;
            *(uint32_t*)((intptr_t)this + 0x1ac) = (uint32_t)pRec[2];
            break;
        }
        }

        // Advance to next token
        if (!bIsSparse) {
            // Linked list style: advance pointer by the size of current token
            if ((int32_t)tokenIndex < 0) {
                ppCurrentToken = (void**)((intptr_t)ppCurrentToken + (intptr_t)*ppCurrentToken);
                streamAdvanceFrame();
                tokenIndex = tokenDword; // local_58
            }
            else if ((int32_t)tokenIndex < (int32_t)(tokenCount - 1)) {
                ppCurrentToken = (void**)((intptr_t)ppCurrentToken + (intptr_t)*ppCurrentToken);
                tokenIndex++;
                tokenDword = tokenIndex;
            }
            else {
                ppCurrentToken = (void**)0x01163cf8; // sentinel? (maybe end marker)
                ppCurrentToken = (void**)0x01163cf8;
            }
        }
        else {
            // Sparse array: use bitmask to skip empty slots
            tokenIndex++;
            tokenDword = tokenIndex;
            if (tokenIndex != tokenCount) {
                tokenShort = (uint16_t)tokenIndex;
                // Check if this index is present in the bitmask
                uint8_t byteMask = bitmaskBase[tokenIndex >> 3];
                uint8_t bitMask = 1 << (tokenIndex & 7);
                if ((byteMask & bitMask) == 0) {
                    tokenDword = (uint32_t)pTokenBuffer; // reuse local
                    tokenDword = *(uint32_t*)pTokenBuffer; // read next from buffer
                    pTokenBuffer = (void**)((intptr_t)pTokenBuffer + 4);
                }
                else {
                    tokenDword = 0;
                    tokenDword = 0;
                }
            }
        }
    }

    // Post‑loop conditional flag setting
    if (*(uintptr_t*)((intptr_t)this + 0x1a8) != 0) {
        *(uint32_t*)((intptr_t)this + 0x1ac) |= 2;
    }
    else {
        *(uint32_t*)((intptr_t)this + 0x1ac) &= ~2;
    }
}