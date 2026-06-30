// FUNC_NAME: tolua_gc
int tolua_gc(lua_State* L)
{
    // L->top is at +0xC (current stack top pointer)
    // L->base is at +0x8 (stack base)
    // L->globalState is at +0x10 (points to internal GC state)
    int* top = *(int**)(L + 0xC);
    bool result = false;

    // Check if stack is not empty and top is valid
    if (top < *(int**)(L + 0x8) && top != nullptr)
    {
        int type = *top;
        // Only handle userdata (7) and lightuserdata (2)
        if (type == 7 || type == 2)
        {
            void* value;
            if (type == 2)
                value = (void*)top[1];               // Lightuserdata: pointer directly
            else if (type == 7)
                value = (void*)(top[1] + 0x10);      // Userdata: pointer at offset +0x10 in userdata structure
            else
                value = nullptr;

            // Access global state for GC
            int* globalState = *(int**)(L + 0x10);
            // Reset GC threshold
            *(int*)(globalState + 0x20) = 0;
            // Check if GC step needed
            if (*(uint*)(globalState + 0x20) <= *(uint*)(globalState + 0x24))
                luaC_step(L);   // Trigger incremental GC step

            // Push the "tolua_gc" function onto the stack (for callback)
            lua_pushstring(L, "tolua_gc");
            lua_pushvalue(L, -1);   // Duplicate the function on stack
            // Now the stack has: [func, func]

            // Modify first stack slot to be a number (2) with the value pointer
            int* stackSlot = *(int**)(L + 0x8);   // Get base pointer
            *stackSlot = 2;                       // Type: number
            stackSlot[1] = (int)value;            // Value: the pointer
            *(int**)(L + 0x8) = stackSlot + 2;   // Move base forward

            // Call GC function via the stack (C function call)
            // FUN_00638020 seems to be a function call mechanism
            // It takes L and an offset into the closure?
            int* back = *(int**)(L + 0x8) - 8;   // Point to the slot we just wrote
            int* callResult = (int*)callFunction(L, *(int*)(back + 0x1c)); // Call the GC function
            *callResult = *(int*)(back + 8);
            callResult[1] = *(int*)(back + 12);
            *(int**)(L + 0x8) = back; // Restore stack pointer

            result = true;
        }
    }

    // Push the return value (boolean)
    int* topPush = *(int**)(L + 0x8);
    *topPush = 1;                       // Type: boolean
    *(int*)(topPush + 1) = result ? 1 : 0;
    *(int**)(L + 0x8) = topPush + 2;   // Increment stack pointer

    return 1;   // Number of return values
}