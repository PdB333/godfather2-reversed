// FUNC_NAME: ScriptStream::readNumberToken
int __thiscall ScriptStream::readNumberToken(void *thisPtr)
{
    // +0x08: int* m_pWritePos (current write pointer in output buffer)
    // +0x0c: ReadState* m_pReadState (current read token state)
    // The ReadState struct stores one 8-byte token at offset +0x08:
    //   +0x08: int tokenType (3 = integer, 4 = float)
    //   +0x0c: int tokenValue (raw int or float as int)
    ReadState *pReadState = *(ReadState **)((char *)thisPtr + 0x0c);
    int *pToken = (int *)((char *)pReadState + 0x08); // points to tokenType field in read state

    int targetType = 3; // initially expect type 3 (integer)
    float secondValue = 0.0f; // store the value of the second token found

    // --- First token search ---
    if (*(int **)((char *)thisPtr + 0x08) > pToken && pToken != NULL)
    {
        // Check if token type is 3 or 4 (with conversion)
        if (*pToken == 3 || (*pToken == 4 && convertTokenToFloat(pToken, &secondValue)))
        {
            float firstValue = *((float *)pToken + 1); // read the value as float
            if (firstValue == FLOAT_SENTINEL) // sentinel value, need to loop for another token
            {
                while (true)
                {
                    pToken = (int *)((char *)pReadState + 0x08); // reset to same token (or maybe read state updates?)
                    if (*(int **)((char *)thisPtr + 0x08) <= pToken || pToken == NULL)
                        break;
                    if (*pToken == targetType || (*pToken == 4 && convertTokenToFloat(pToken, &secondValue)))
                        break; // found token of the expected type
                    targetType = 2;
                    debugPrint(" number"); // error? or indicator
                    // fall through to set secondValue = 0.0
                    secondValue = 0.0f;
                }
            }
            // else: no sentinel, fall through
        }
    }
    // else: invalid token, secondValue remains 0.0

    // --- Second token search (for output value) ---
    pToken = (int *)((char *)pReadState + 0x08);
    if (*(int **)((char *)thisPtr + 0x08) > pToken && pToken != NULL)
    {
        if (*pToken == 3 || (*pToken == 4 && convertTokenToFloat(pToken, &secondValue)))
        {
            float secondCandidate = *((float *)pToken + 1);
            if (secondCandidate == FLOAT_SENTINEL)
            {
                while (true)
                {
                    pToken = (int *)((char *)pReadState + 0x08);
                    if (*(int **)((char *)thisPtr + 0x08) <= pToken || pToken == NULL)
                        break;
                    if (*pToken == targetType || (*pToken == 4 && convertTokenToFloat(pToken, &secondValue)))
                        break;
                    targetType = 1;
                    debugPrint(" number");
                    secondValue = 0.0f;
                }
            }
        }
    }

    // --- Write output token (type = targetType, value = secondValue) ---
    int *writePos = *(int **)((char *)thisPtr + 0x08);
    *writePos = targetType;
    double convDouble = (double)secondValue;
    floatConv(); // likely rounds/casts double to int for writing
    writePos[1] = (int)(float)convDouble; // careful: the decompiler shows (int)(float)dVar4
    // advance write pointer by 8 bytes
    *(int **)((char *)thisPtr + 0x08) = writePos + 2;

    return 1;
}