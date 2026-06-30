// FUNC_NAME: LuaBinding::getPeerTable (tolua internal function)
// Address: 0x0063abc0
// Role: Retrieves the peer table for a userdata from the Lua registry using the "tolua_peer" key, then manipulates the stack to handle method calls or property access.

void LuaBinding::getPeerTable(int luaState) // lua_State* in reality
{
    // Push the key "tolua_peer" onto the stack and get the value from the registry
    lua_get_table(luaState, "tolua_peer"); // FUN_00625ca0

    // Current stack top (points to the just-pushed value)
    int* stackPtr = *(int**)(luaState + 8);
    int typeTag = *(int*)(stackPtr + -8);
    int value = *(int*)(stackPtr + -4);

    if (typeTag == 3) // type 3: number (if conversion check fails, treat as nil)
    {
        if ((float)(int)value != *(float*)(stackPtr + -4)) // integer-to-float check, likely for NaN?
        {
            goto treatAsNil;
        }
        // Get static number type/value
        int* staticVal = (int*)get_static_number(); // FUN_00637f10
        typeTag = *staticVal;
        value = staticVal[1];
    }
    else if (typeTag == 4) // type 4: string?
    {
        // Get static string type/value
        int* staticVal = (int*)get_static_string(); // FUN_00637f90
        typeTag = *staticVal;
        value = staticVal[1];
    }
    else
    {
treatAsNil:
        // Get static nil type/value
        int* staticVal = (int*)get_static_nil(); // FUN_00637ea0
        typeTag = *staticVal;
        value = staticVal[1];
    }

    // Overwrite the top of the stack with the resolved value
    *(int*)(stackPtr + -8) = typeTag;
    *(int*)(stackPtr + -4) = value;

    // Now handle the peer table: copy the value from the next stack slot (at param_1+0xc) to the top
    int* src = *(int**)(luaState + 0xc);
    int* dst = *(int**)(luaState + 8);
    *dst = *src;
    dst[1] = src[1];
    *(int**)(luaState + 8) = dst + 2; // advance stack pointer

    // Now inspect the new top (the just-copied value)
    int* newTop = *(int**)(luaState + 8);
    int tag = *(int*)(newTop + -8);
    int val = *(int*)(newTop + -4);

    if (tag == 3)
    {
        if ((float)(int)val != *(float*)(newTop + -4))
        {
            // Fall through to nil
        }
        else
        {
            int* staticVal2 = (int*)get_static_number(); // FUN_00637f10
            tag = *staticVal2;
            val = staticVal2[1];
            goto doneTag;
        }
    }
    else if (tag == 4)
    {
        int* staticVal2 = (int*)get_static_string(); // FUN_00637f90
        tag = *staticVal2;
        val = staticVal2[1];
        goto doneTag;
    }
    // default: nil
    {
        int* staticVal2 = (int*)get_static_nil(); // FUN_00637ea0
        tag = *staticVal2;
        val = staticVal2[1];
    }
doneTag:
    *(int*)(newTop + -8) = tag;
    *(int*)(newTop + -4) = val;

    // Check if the value just popped is a function (type 5)
    int* checkPtr = (int*)(*(int*)(luaState + 8) + -8);
    if (checkPtr == 0 || *checkPtr != 5)
    {
        // Not a function: roll back stack and push a nil function placeholder
        *(int**)(luaState + 8) = checkPtr;
        if (*(unsigned int*)(*(int*)(luaState + 0x10) + 0x20) <= *(unsigned int*)(*(int*)(luaState + 0x10) + 0x24))
        {
            stack_full_handler(); // FUN_00627360
        }
        int* funcSlot = *(int**)(luaState + 8);
        *funcSlot = 5; // type = function
        funcSlot[1] = create_new_userdata(0, 0); // FUN_00637c50
        *(int**)(luaState + 8) = funcSlot + 2;

        // Copy the original value from source again
        int* src2 = *(int**)(luaState + 0xc);
        int* dst2 = *(int**)(luaState + 8);
        *dst2 = *src2;
        dst2[1] = src2[1];
        *(int**)(luaState + 8) = dst2 + 2;

        // Copy the top 8 bytes down (shift stack down?)
        int* copySrc = *(int**)(luaState + 8);
        copySrc[0] = copySrc[-4];
        copySrc[1] = copySrc[-3];
        *(int**)(luaState + 8) = copySrc + 2;

        // Call indexing function with offset -0x1c (function arguments?)
        int* base = *(int**)(luaState + 8);
        int* result = (int*)stack_index(luaState, *(int*)(base + -0x1c)); // FUN_00638020
        result[0] = *(int*)(base + -8);
        result[1] = *(int*)(base + -4);
        *(int**)(luaState + 8) = base + (-0x10);
    }

    // Compact the stack: move values up by 8 bytes (2 slots) to remove a gap
    int* stack = *(int**)(luaState + 8);
    int* iter = stack;
    while (stack + -8 < iter) // while there is space below
    {
        iter[0] = iter[-2];
        iter[1] = iter[-1];
        iter += 2;
    }
    int* top = *(int**)(luaState + 8);
    stack[-8] = *top;
    stack[-7] = top[1];
    *(int**)(luaState + 8) = stack + (-8);

    // Call indexing function again with offset -0x14
    int* base2 = *(int**)(luaState + 8);
    int* result2 = (int*)stack_index(luaState, *(int*)(base2 + -0x14)); // FUN_00638020
    result2[0] = *(int*)(base2 + -8);
    result2[1] = *(int*)(base2 + -4);
    *(int**)(luaState + 8) = base2 + (-0x18);
    return;
}