// FUNC_NAME: tolua_peer
// Address: 0x0063abc0
// Implements the tolua_peer operation: retrieves the peer table associated with a userdata on the Lua stack.
void tolua_peer(lua_State* L) {
    // Push the string "tolua_peer" onto the stack (for error messages or type checking)
    tolua_peekstring(L, "tolua_peer");

    // Current stack top pointer (points to the first free slot)
    int* stackPtr = (int*)L->stackTop; // Offset +0x08: pointer to current top of stack

    // Get the value at stackPtr[-2] (type) and stackPtr[-1] (value)
    int type = *(int*)(stackPtr - 8);  // Type tag at offset -8 bytes (two 4-byte slots)
    int value = *(int*)(stackPtr - 4); // Value at offset -4 bytes

    if (type == 3) {
        // Type is number – check if the float value is actually an integer
        float fVal = *(float*)&value;
        if ((float)(int)fVal == fVal) {
            // This is a round integer -> convert using integer converter
            int* result = (int*)convertToInt(); // FUN_00637f10 returns a pointer to type+value pair
            *(stackPtr - 8) = result[0]; // Replace type
            *(stackPtr - 4) = result[1]; // Replace value
        } else {
            goto defaultConvert;
        }
    } else if (type == 4) {
        // Type is boolean -> convert using boolean converter
        int* result = (int*)convertToBool(); // FUN_00637f90
        *(stackPtr - 8) = result[0];
        *(stackPtr - 4) = result[1];
    } else {
defaultConvert:
        // Other types -> default converter (e.g., nil or userdata)
        int* result = (int*)convertDefault(); // FUN_00637ea0
        *(stackPtr - 8) = result[0];
        *(stackPtr - 4) = result[1];
    }

    // Copy two values from the base pointer (usually the table or function argument)
    int* basePtr = (int*)L->base; // Offset +0x0C: base of the current function stack
    *(stackPtr) = *basePtr;      // Copy first value to current top
    *(stackPtr + 1) = *(basePtr + 1);
    L->stackTop = stackPtr + 8;  // Advance stack top by 8 bytes (one slot)

    // Now process the next value (the userdata itself)
    int* newTop = (int*)L->stackTop;
    int type2 = *(int*)(newTop - 8);
    int value2 = *(int*)(newTop - 4);

    if (type2 == 3) {
        float fVal = *(float*)&value2;
        if ((float)(int)fVal == fVal) {
            int* result = (int*)convertToInt();
            *(newTop - 8) = result[0];
            *(newTop - 4) = result[1];
            goto checkType5;
        }
    } else if (type2 == 4) {
        int* result = (int*)convertToBool();
        *(newTop - 8) = result[0];
        *(newTop - 4) = result[1];
        goto checkType5;
    }
    // Default conversion
    int* result = (int*)convertDefault();
    *(newTop - 8) = result[0];
    *(newTop - 4) = result[1];

checkType5:
    // Check if the current top slot has type 5 (nil? or another marker)
    int* testPtr = (int*)L->stackTop - 8;
    if (testPtr == nullptr || *testPtr != 5) {
        L->stackTop = (int*)testPtr; // Pop back to this position
        // Check if stack has room for more elements
        if (*(int*)(*(int*)(L + 0x10) + 0x20) <= *(int*)(*(int*)(L + 0x10) + 0x24)) {
            expandStack(L); // FUN_00627360 – grow the stack
        }
        // Write type 5 marker and a value from some source
        int* current = (int*)L->stackTop;
        *current = 5; // Type 5 (might be nil or table ref)
        int newVal = getSomeValue(0, 0); // FUN_00637c50
        *(current + 1) = newVal;
        L->stackTop = current + 8; // Advance again

        // Copy two values from base again
        int* base = (int*)L->base;
        *(current + 2) = *base;
        *(current + 3) = *(base + 1);
        L->stackTop = current + 16; // Advance by 16 bytes (two slots)

        // Copy values from earlier position on stack
        int* top = (int*)L->stackTop;
        *top = *(top - 4);   // Copy from slot -4
        *(top + 1) = *(top - 3);
        L->stackTop = top + 8;

        // More complex stack manipulation: push result from another converter
        int* temp = (int*)L->stackTop;
        int* resultPtr = (int*)convertAndPush(L, *(int*)(temp - 0x1c)); // FUN_00638020 returns pointer
        *resultPtr = *(temp - 8);
        *(resultPtr + 1) = *(temp - 4);
        L->stackTop = temp - 16;
    }

    // Final stack reordering: shift elements
    int* base = (int*)L->base; // Actually points to the beginning of this stack frame
    int* src = (int*)L->stackTop;
    int* dst = src - 8; // destination is 8 bytes before the original top
    // Move elements forward by 8 bytes (one slot) for the entire stack from base to src
    for (int* p = src; p < src + 8; p += 2) {
        *p = *(p + 2);
        *(p + 1) = *(p + 3);
    }
    // Place the previously saved values at the base
    int* top = (int*)L->stackTop;
    *(top - 8) = *(top - 0);
    *(top - 7) = *(top + 1);
    L->stackTop = top - 8; // Move stack pointer back by 8 bytes

    // Final push of a converted value
    int* final = (int*)L->stackTop;
    int* resultFinal = (int*)convertAndPush(L, *(int*)(final - 0x14)); // FUN_00638020
    *resultFinal = *(final - 8);
    *(resultFinal + 1) = *(final - 4);
    L->stackTop = final - 24; // Adjust stack top by -24 bytes (three slots)
}