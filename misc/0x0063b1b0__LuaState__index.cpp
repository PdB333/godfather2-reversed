//FUNC_NAME: LuaState::index
// Address: 0x0063b1b0
// Role: Lua __index metamethod for userdata and table types (tolua binding)

int LuaState::index(int state) // state is a pointer to Lua stack structure
{
    int *stackTop = *(int **)(state + 0xc); // +0xc: current stack top pointer
    int *stackBase = *(int **)(state + 0x8); // +0x8: stack base pointer
    int *stackEnd; // +0x10: stack end pointer (used for bounds)
    int type;
    int *valuePtr;
    int *tempPtr;
    int *srcPtr;
    int *dstPtr;
    char buffer[8]; // used for string comparison

    // Check if stack is non-empty and top is within bounds
    if ((stackTop < stackBase) && (stackTop != nullptr))
    {
        type = *stackTop;
        if (type == 7) // LUA_TUSERDATA
        {
            // Handle userdata indexing
            pushString(state, "tolua_peer");
            stackPop(); // FUN_00625e70 - pop stack
            // Copy top two values to base
            srcPtr = *(int **)(state + 0xc);
            dstPtr = *(int **)(state + 0x8);
            *dstPtr = *srcPtr;
            dstPtr[1] = srcPtr[1];
            *(int *)(state + 0x8) += 8; // advance base
            stackPop();
            srcPtr = *(int **)(state + 0x8);
            // Check if previous value is a table (type 5)
            if ((srcPtr - 2 != nullptr) && (srcPtr[-2] == 5))
            {
                int base = *(int *)(state + 0xc);
                *srcPtr = *(int *)(base + 8);
                srcPtr[1] = *(int *)(base + 0xc);
                *(int *)(state + 0x8) += 8;
                stackPop();
                srcPtr = *(int **)(state + 0x8);
                if (srcPtr - 2 == nullptr)
                    return 1;
                if (srcPtr[-2] != 0) // not nil
                    return 1;
            }
            // Fill remaining stack slots with nil (0)
            if (srcPtr < (int *)(*(int *)(state + 0xc) + 0x10))
            {
                do
                {
                    **(int **)(state + 0x8) = 0;
                    *(int *)(state + 0x8) += 8;
                } while (*(unsigned int *)(state + 0x8) < (unsigned int)(*(int *)(state + 0xc) + 0x10));
            }
            // Reset stack top and copy original values
            srcPtr = *(int **)(state + 0xc);
            *(int **)(state + 0x8) = srcPtr + 4;
            srcPtr[4] = *srcPtr;
            srcPtr[5] = srcPtr[1];
            *(int *)(state + 0x8) += 8;

            // Main loop: process indexing chain
            while (true)
            {
                srcPtr = *(int **)(state + 0x8);
                if (srcPtr - 2 == nullptr)
                    break;
                int valType = srcPtr[-2];
                int val;
                if (valType == 5) // table
                {
                    val = *(int *)(srcPtr[-1] + 8);
                }
                else if (valType == 7) // userdata
                {
                    val = *(int *)(srcPtr[-1] + 8);
                }
                else
                {
                    break;
                }
                // Check if val is 0 or matches a sentinel (likely metatable)
                if ((val == 0) || (val == *(int *)(*(int *)(state + 0x10) + 0x38)))
                    break;
                // Push a table type with the value
                *srcPtr = 5;
                srcPtr[1] = val;
                *(int *)(state + 0x8) += 8;
                // Shift stack to make room
                srcPtr = *(int **)(state + 0x8) - 2;
                if (srcPtr < *(int **)(state + 0x8))
                {
                    do
                    {
                        srcPtr[-2] = *srcPtr;
                        srcPtr[-1] = srcPtr[1];
                        srcPtr += 2;
                    } while (srcPtr < *(int **)(state + 0x8));
                }
                *(int *)(state + 0x8) -= 8;
                // Check for indexing operation (geti)
                int *checkPtr = (int *)(*(int *)(state + 0xc) + 8);
                if (((checkPtr < *(int **)(state + 0x8)) && (checkPtr != nullptr)) &&
                    ((*checkPtr == 3) || ((*checkPtr == 4) && (compareString(buffer) != 0))))
                {
                    pushString(state, ".geti");
                    int top = *(int *)(state + 0x8);
                    int topType = *(int *)(top - 8);
                    int *newVal;
                    if (topType == 3) // number
                    {
                        if ((float)(int)*(float *)(top - 4) != *(float *)(top - 4))
                            goto convertGeneric;
                        newVal = (int *)convertNumberToInteger(); // FUN_00637f10
                    }
                    else if (topType == 4) // string
                    {
                        newVal = (int *)convertStringToNumber(); // FUN_00637f90
                    }
                    else
                    {
convertGeneric:
                        newVal = (int *)convertToGeneric(); // FUN_00637ea0
                    }
                    *(int *)(top - 8) = *newVal;
                    *(int *)(top - 4) = newVal[1];
                    int result = getType(); // FUN_00625740
                    if (result == 6) // function
                    {
                        goto copyAndReturn;
                    }
                }
                else
                {
                    // Direct indexing without .geti
                    int base = *(int *)(state + 0xc);
                    srcPtr = *(int **)(state + 0x8);
                    *srcPtr = *(int *)(base + 8);
                    srcPtr[1] = *(int *)(base + 0xc);
                    *(int *)(state + 0x8) += 8;
                    int top = *(int *)(state + 0x8);
                    int topType = *(int *)(top - 8);
                    int *newVal;
                    if (topType == 3)
                    {
                        if ((float)(int)*(float *)(top - 4) != *(float *)(top - 4))
                            goto convertGeneric2;
                        newVal = (int *)convertNumberToInteger();
                    }
                    else if (topType == 4)
                    {
                        newVal = (int *)convertStringToNumber();
                    }
                    else
                    {
convertGeneric2:
                        newVal = (int *)convertToGeneric();
                        top = *(int *)(state + 0x8);
                    }
                    *(int *)(top - 8) = *newVal;
                    *(int *)(top - 4) = newVal[1];
                    int result = getType();
                    if (result != 0)
                        return 1;
                    // Pop and push ".self"
                    *(int *)(state + 0x8) -= 8;
                    pushString(state, ".self");
                    int top2 = *(int *)(state + 0x8);
                    int topType2 = *(int *)(top2 - 8);
                    int *newVal2;
                    if (topType2 == 3)
                    {
                        if ((float)(int)*(float *)(top2 - 4) != *(float *)(top2 - 4))
                            goto convertGeneric3;
                        newVal2 = (int *)convertNumberToInteger();
                    }
                    else if (topType2 == 4)
                    {
                        newVal2 = (int *)convertStringToNumber();
                    }
                    else
                    {
convertGeneric3:
                        newVal2 = (int *)convertToGeneric();
                    }
                    *(int *)(top2 - 8) = *newVal2;
                    *(int *)(top2 - 4) = newVal2[1];
                    int result2 = getType2(); // FUN_00625790
                    if (result2 != 0)
                        goto copyAndReturn;
                    int result3 = getType(); // FUN_00625740
                    if (result3 == 5) // table
                    {
                        int *basePtr = *(int **)(state + 0xc);
                        int *selfVal;
                        if ((basePtr < *(int **)(state + 0x8)) && (basePtr != nullptr))
                        {
                            if (*basePtr == 2) // lightuserdata
                            {
                                selfVal = (int *)basePtr[1];
                            }
                            else if (*basePtr == 7) // userdata
                            {
                                selfVal = (int *)(basePtr[1] + 0x10);
                            }
                            else
                            {
                                selfVal = nullptr;
                            }
                        }
                        else
                        {
                            selfVal = nullptr;
                        }
                        int self = *selfVal;
                        stackPop(); // FUN_00625f40
                        pushString(state, ".self");
                        srcPtr = *(int **)(state + 0x8);
                        srcPtr[1] = self;
                        *srcPtr = 2; // lightuserdata
                        *(int *)(state + 0x8) += 8;
                        int top3 = *(int *)(state + 0x8);
                        int *newVal3 = (int *)getUserdata(state, *(int *)(top3 - 0x14)); // FUN_00638020
                        *newVal3 = *(int *)(top3 - 8);
                        newVal3[1] = *(int *)(top3 - 4);
                        *(int *)(state + 0x8) -= 0x10;
                        // Shift stack to remove old values
                        srcPtr = *(int **)(state + 0x8);
                        for (dstPtr = srcPtr; srcPtr - 4 < dstPtr; dstPtr -= 2)
                        {
                            *dstPtr = dstPtr[-2];
                            dstPtr[1] = dstPtr[-1];
                        }
                        dstPtr = *(int **)(state + 0x8);
                        srcPtr[-4] = *dstPtr;
                        srcPtr[-3] = dstPtr[1];
                        stackSwap(); // FUN_00626130
                        srcPtr = *(int **)(state + 0x8);
                        *srcPtr = srcPtr[-2];
                        srcPtr[1] = srcPtr[-1];
                        *(int *)(state + 0x8) += 8;
                        int base2 = *(int *)(state + 0xc);
                        srcPtr = *(int **)(state + 0x8);
                        *srcPtr = *(int *)(base2 + 8);
                        srcPtr[1] = *(int *)(base2 + 0xc);
                        *(int *)(state + 0x8) += 8;
                        // Shift again
                        srcPtr = *(int **)(state + 0x8);
                        for (dstPtr = srcPtr; srcPtr - 4 < dstPtr; dstPtr -= 2)
                        {
                            *dstPtr = dstPtr[-2];
                            dstPtr[1] = dstPtr[-1];
                        }
                        dstPtr = *(int **)(state + 0x8);
                        srcPtr[-4] = *dstPtr;
                        srcPtr[-3] = dstPtr[1];
                        callMetamethod(state); // FUN_0063abc0
                        return 1;
                    }
                }
                // Fill remaining with nil up to base+0x18
                if (*(unsigned int *)(state + 0x8) < (unsigned int)(*(int *)(state + 0xc) + 0x18))
                {
                    do
                    {
                        **(int **)(state + 0x8) = 0;
                        *(int *)(state + 0x8) += 8;
                    } while (*(unsigned int *)(state + 0x8) < (unsigned int)(*(int *)(state + 0xc) + 0x18));
                }
                *(int *)(state + 0x8) = *(int *)(state + 0xc) + 0x18;
            }
            // Final nil push
            **(int **)(state + 0x8) = 0;
            *(int *)(state + 0x8) += 8;
            return 1;
        }
        else if (type == 5) // LUA_TTABLE
        {
            // Handle table indexing (delegate to another function)
            tableIndex(state); // FUN_0063ad70
            return 1;
        }
    }
    // Default: push nil
    **(int **)(state + 0x8) = 0;
    *(int *)(state + 0x8) += 8;
    return 1;

copyAndReturn:
    // Copy top two values from base to top and return
    srcPtr = *(int **)(state + 0xc);
    dstPtr = *(int **)(state + 0x8);
    *dstPtr = *srcPtr;
    dstPtr[1] = srcPtr[1];
    int base = *(int *)(state + 0xc);
    *(int *)(state + 0x8) += 8;
    srcPtr = *(int **)(state + 0x8);
    *srcPtr = *(int *)(base + 8);
    srcPtr[1] = *(int *)(base + 0xc);
    *(int *)(state + 0x8) += 8;
    callMetamethod(state, *(int *)(state + 0x8) - 0x18, 1); // FUN_006362d0
    return 1;
}