// 0x004c8510: LuaSendMsg - Sends a game message from Lua, expects a single string argument (message ID) and optionally a payload (float, string, or table)
int LuaSendMsg(void* luaState) // __cdecl, uses stack-based argument access
{
    char cVar1;
    void* pcVar2;
    char* stringData;
    float* floatPtr;
    int result;
    int argIndex;
    float* payload;
    int stackPtr;
    int* currentArg;    // pointer to current Lua stack value (16 bytes each)
    float10 tempFloat;  // extended precision float
    char* lengthStr;
    float localFloat[2]; // buffer for float value

    // Get current stack pointer (points to top of arguments)
    currentArg = *(int**)((int)luaState + 0x0c);
    // Check if there is at least one argument (stack not empty)
    if ((currentArg < *(int**)((int)luaState + 8)) && (currentArg != (int*)0x0))
    {
        // Process first argument (message ID)
        if (*currentArg == 4) // type string
        {
            // The data starts 0x10 bytes into the string buffer pointed by currentArg[1]
            argIndex = currentArg[1] + 0x10;
        }
        else
        {
            // Try to convert to string or handle error
            argIndex = checkStackElement(luaState);
            if (argIndex == 0)
            {
                argIndex = 0;
            }
            else
            {
                argIndex = currentArg[1] + 0x10;
            }
            // Stack overflow check (some internal counter)
            if (*(uint*)(*(int*)((int)luaState + 0x10) + 0x20) <= *(uint*)(*(int*)((int)luaState + 0x10) + 0x24))
            {
                handleStackOverflow();
            }
        }
        if (argIndex != 0)
        {
            // Process second argument (optional? - always a table or string?)
            stackPtr = *(int*)((int)luaState + 0x0c);
            currentArg = (int*)(stackPtr + 8); // move to next element (16 bytes apart)
            if ((currentArg < *(int**)((int)luaState + 8)) && (currentArg != (int*)0x0))
            {
                if (*currentArg == 4) // string
                {
                    argIndex = *(int*)(stackPtr + 0x0c) + 0x10;
                }
                else
                {
                    int iVar4 = checkStackElement(luaState);
                    if (iVar4 == 0)
                    {
                        argIndex = 0;
                    }
                    else
                    {
                        argIndex = *(int*)(stackPtr + 0x0c) + 0x10;
                    }
                    if (*(uint*)(*(int*)((int)luaState + 0x10) + 0x20) <= *(uint*)(*(int*)((int)luaState + 0x10) + 0x24))
                    {
                        handleStackOverflow();
                    }
                }
            }
            else
            {
                argIndex = 0;
            }

            // Process third argument (payload)
            floatPtr = (float*)0x0;
            lengthStr = (char*)0x0;
            localFloat[0] = 0.0f;
            payload = (float*)0x0;
            if (argIndex != 0)
            {
                stackPtr = *(int*)((int)luaState + 0x0c);
                currentArg = (int*)(stackPtr + 0x10); // third element
                if ((currentArg < *(int**)((int)luaState + 8)) && (currentArg != (int*)0x0))
                {
                    argIndex = *currentArg; // type of third argument
                }
                else
                {
                    argIndex = -1; // invalid
                }

                if (argIndex == 3) // float
                {
                    tempFloat = (float10)getFloatFromStack(luaState, 3);
                    localFloat[0] = (float)tempFloat;
                    payload = localFloat;
                }
                else if (argIndex == 4) // string
                {
                    stringData = getStringFromStack(luaState, 3);
                    payload = floatPtr;
                    if (stringData != (char*)0x0)
                    {
                        lengthStr = stringData;
                        // calculate string length
                        do
                        {
                            cVar1 = *lengthStr;
                            lengthStr = lengthStr + 1;
                        } while (cVar1 != '\0');
                        lengthStr = lengthStr + (1 - (int)(stringData + 1)); // length including null? 
                        payload = (float*)heapAlloc(0, lengthStr);
                        _memcpy(payload, stringData, (size_t)lengthStr);
                        floatPtr = payload; // save for later free
                    }
                }
                else if (argIndex == 7) // table (or object)
                {
                    if ((currentArg < *(int**)((int)luaState + 8)) && (currentArg != (int*)0x0))
                    {
                        if (*currentArg == 2) // inner type? (maybe float table)
                        {
                            payload = *(float**)(stackPtr + 0x14);
                        }
                        else if (*currentArg == 7) // nested table?
                        {
                            payload = (float*)(*(int*)(stackPtr + 0x14) + 0x10);
                        }
                        else
                        {
                            payload = (float*)0x0;
                        }
                    }
                    else
                    {
                        payload = (float*)0x0;
                    }
                }
                else
                {
                    payload = (float*)0x0;
                }
            }
            // Send the message with the extracted payload
            sendGameMessage(payload);
            // Free allocated string if any
            if (floatPtr != (float*)0x0)
            {
                heapFree(floatPtr);
                // Decrease memory counter
                int* counter = (int*)(*(int*)((int)luaState + 0x10) + 0x24);
                *counter = *counter - (int)lengthStr;
            }
            return 1;
        }
    }
    // Error: expected a string argument
    printError("LuaSendMsg expects a single string argument (the message id)\n");
    pcVar2 = (code*)swi(3); // crash
    result = (*pcVar2)();
    return result;
}