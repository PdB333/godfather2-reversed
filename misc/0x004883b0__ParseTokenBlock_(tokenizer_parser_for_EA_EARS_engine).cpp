// FUNC_NAME: ParseTokenBlock (tokenizer/parser for EA EARS engine)
void ParseTokenBlock(char* pInputString, float fDurationScale, int* pAccumulatedCount, float fTimeMultiplier,
                     int* pContext, int* pOutputPosition, float* pMaxTime, char* pCharOut, char bPreprocess)
{
    // Local variables
    char* pCurrentPos;
    char cCurrentChar;
    int iTokenLength;
    int iTokenCount;
    float fTokenValue;
    char cTokenType;
    int iOffset;
    int iLineNum;
    int iCharCode;
    char* pBufferStart;
    int iBufferOffset;
    int iSomeCounter;
    short sCharState;
    int iPreprocessResult;
    char* pPreprocessedBuf;
    int iPreprocessedOffset;
    int iPreprocessedCounter;
    short sPreprocessedState;
    int iPreprocessResult2;
    float fAccumulatedTime;
    float fCurrentTime;
    char cTemp;
    int iTemp1;
    int iTemp2;
    float fTemp;
    char cTempFlag;
    char localBuf[2048];

    // Initialize time accumulator
    float fDivisor = (float)pContext[3];  // pContext[3] = offset 0xC, scaling divisor
    fDurationScale = fDurationScale / fDivisor;

    fAccumulatedTime = 0.0f;
    pBufferStart = pInputString;
    iBufferOffset = 0;
    iSomeCounter = 0;
    sCharState = 0;

    int iCharCodeInit = FUN_004dd960();  // likely readCharFromStream
    iCharCode = iCharCodeInit;

    // Preprocessing step: if flag set and a callback exists, run preprocessor
    if ((bPreprocess != '\0') && ((code*)pContext[9] != (code*)0x0))  // pContext[9] = offset 0x24, callback
    {
        cTemp = ((code*)pContext[9])(pInputString, localBuf, 0x800, 0);  // preprocess input
        if (cTemp != '\0')
        {
            pPreprocessedBuf = localBuf;
            iPreprocessedOffset = 0;
            iPreprocessedCounter = 0;
            sPreprocessedState = 0;
            FUN_004dd960();  // read first char from preprocessed buffer
            iBufferOffset = iPreprocessedOffset;
            pBufferStart = pPreprocessedBuf;
            sCharState = sPreprocessedState;
            iSomeCounter = iPreprocessedCounter;
        }
    }

    // Clear output char
    if (pCharOut != (char*)0x0)
    {
        *pCharOut = '\0';
    }

    // Compute initial max time from context data
    if (pMaxTime != (float*)0x0)
    {
        float fBase = 0.0f;
        if (*pContext != 0)  // pContext[0] is pointer to some object
        {
            fBase = (float)*(int*)(*pContext + 0x18) * (float)pContext[4];  // offset 0x18 and pContext[4]=0x10
        }
        *pMaxTime = fBase * fTimeMultiplier;
    }

    // Main parsing loop
    if (*pContext != 0)
    {
        while (true)
        {
            // Check for end-of-line characters
            if (((sCharState == 0) || (sCharState == 0xa)) || (sCharState == 0xd))
                goto LAB_0048872d;

            pCurrentPos = pBufferStart + iBufferOffset;

            // Read current character
            iPreprocessedOffset = 0;
            iPreprocessedCounter = 0;
            sPreprocessedState = 0;
            pPreprocessedBuf = pCurrentPos;
            FUN_004dd960();  // updates stack variables, reads char to sPreprocessedState
            if (sPreprocessedState == 0x5c)  // backslash
            {
                iPreprocessedOffset = 0;
                iPreprocessedCounter = 0;
                sPreprocessedState = 0;
                pPreprocessedBuf = pCurrentPos;
                iPreprocessResult2 = FUN_004dd960();  // read next char
                iPreprocessedOffset = iPreprocessedOffset + iPreprocessResult2;
                FUN_004dd960();  // advance pointer?
                if (sPreprocessedState == 0x6e)  // 'n' -> newline escape
                    goto LAB_0048872d;
            }

            // Reset token extraction locals
            fCurrentTime = 0.0f;
            iTokenLength = 0;
            iTokenCount = 0;
            fTokenValue = 0.0f;
            cTokenType = '\0';

            // Extract token from current position
            FUN_00487e30(pContext, &iTokenLength, &iTokenCount, &fTokenValue, &cTokenType);  // extractToken

            // Set output char if provided
            if ((pCharOut != (char*)0x0) && (cTokenType != '\0'))
            {
                *pCharOut = cTokenType;
            }

            // Update max time if token value is larger
            if ((pMaxTime != (float*)0x0) && (fTokenValue * fTimeMultiplier > *pMaxTime))
            {
                *pMaxTime = fTokenValue * fTimeMultiplier;
            }

            // Accumulate time and check if we exceeded duration
            fCurrentTime = fCurrentTime * fTimeMultiplier + fAccumulatedTime;  // actually fCurrentTime=0, so just fAccumulatedTime
            if (fDurationScale < fCurrentTime)
                break;

            int iTempLength = iTokenLength;
            fAccumulatedTime = fCurrentTime;
            if (0 < iTokenLength)
            {
                do
                {
                    iBufferOffset = iBufferOffset + iCharCode;  // advance by character code? likely byte size
                    iCharCode = FUN_004dd960();  // read next char
                    iSomeCounter = iSomeCounter + 1;
                    iTempLength = iTempLength + -1;
                    iCharCode = iCharCode;
                } while (iTempLength != 0);
            }
            *pAccumulatedCount = *pAccumulatedCount + iTokenCount;
        }

        // If no progress was made (position unchanged)
        if (pBufferStart + iBufferOffset == pInputString)
        {
            double dGlobalThreshold = DAT_00e44768;  // global threshold
            if ((double)fTimeMultiplier <= dGlobalThreshold)
            {
                // Skip to end of line
                do
                {
                    cCurrentChar = *pInputString;
                    pInputString = pInputString + 1;
                } while (cCurrentChar != '\0');
                FUN_004ddbc0();  // skipLine
                FUN_004ddc00();  // nextLine
            }
            else
            {
                // Peek next token
                iTokenLength = 0;
                iTokenCount = 0;
                fTokenValue = 0.0f;
                FUN_00487e30(pContext, &iTokenLength, &iTokenCount, &fTokenValue, &cTokenType);
                if ((pCharOut != (char*)0x0) && (cTokenType != '\0'))
                {
                    *pCharOut = cTokenType;
                }
                if ((pMaxTime != (float*)0x0) && (fTokenValue * fTimeMultiplier > *pMaxTime))
                {
                    *pMaxTime = fTokenValue * fTimeMultiplier;
                }
                FUN_004ddc60(iTokenLength);  // handleTokenLength
                *pAccumulatedCount = iTokenCount;
            }
        }
    }

LAB_0048872d:
    if (pOutputPosition != (int*)0x0)
    {
        char* pEndPos = pBufferStart + iBufferOffset;
        *pOutputPosition = (int)pEndPos;
        char cEnd = *pEndPos;
        if (cEnd != '\0')
        {
            if ((cEnd == '\n') || (cEnd == '\r'))
            {
                *pOutputPosition = (int)(pEndPos + 1);
            }
            char* pAdj = (char*)*pOutputPosition;
            if ((*pAdj == '\\') && (pAdj[1] == 'n'))
            {
                *pOutputPosition = (int)(pAdj + 2);
            }
            char cSpace = *(char*)*pOutputPosition;
            while (cSpace == ' ')
            {
                *pOutputPosition = *pOutputPosition + 1;
                cSpace = *(char*)*pOutputPosition;
            }
        }
    }
    return;
}