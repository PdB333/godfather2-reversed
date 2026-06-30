// FUNC_NAME: luaB_setfenv
// Address: 0x0062dd90
// Role: Implements the Lua 'setfenv' function for the EARS Lua engine.
// This function sets the environment table for a function or thread.

int luaB_setfenv(lua_State* L) {
    // L->top is at offset 0x8, L->ci at offset 0xc
    int* ciFunc = (int*)(*(int*)(L + 0xc) + 8); // ci->func (the function being called)
    int* top = *(int**)(L + 0x8); // L->top

    // Check that the first argument is a table (type 5)
    if ((top <= ciFunc) || (ciFunc == nullptr) || (*ciFunc != 5)) {
        luaL_checkType(L, "table"); // Actually luaL_typerror(L, 1, "table")
    }

    // Ensure stack space (likely lua_checkstack)
    lua_checkStack(L);

    // Check if the environment is protected (has a metatable with __metatable)
    int protected = lua_getEnvironment(L); // Returns non-zero if protected
    if (protected != 0) {
        luaL_error(L, "`setfenv' cannot change a protected environment");
    }

    // Adjust stack: pop two values (function and new environment?)
    *(int*)(L + 0x8) = *(int*)(L + 0x8) - 0x10; // L->top -= 2 * sizeof(TValue)

    // Push the function's closure onto stack (from ci->func)
    int* ci = *(int**)(L + 0xc);
    int* newTop = *(int**)(L + 0x8);
    *newTop = *(int*)(ci + 8);       // ci->func.value
    *(newTop + 1) = *(int*)(ci + 0xc); // ci->func.tt
    *(int*)(L + 0x8) = *(int*)(L + 0x8) + 8; // L->top += 1

    // Check if the next value on stack is a function (type 3) or C function (type 4) and not nil
    int* nextVal = *(int**)(L + 0xc);
    if (((nextVal < *(int**)(L + 0x8)) && (nextVal != nullptr)) &&
        ((*nextVal == 3) || ((*nextVal == 4) && (lua_isFunction(L) != 0))) &&
        (lua_setFenv(L, 1) == 0.0f)) {
        // Success: store the new environment and return 0
        *(int*)(L + 0x40) = *(int*)(*(int*)(L + 0x8) - 8);   // L->top[-2].value
        *(int*)(L + 0x44) = *(int*)(*(int*)(L + 0x8) - 4);   // L->top[-2].tt
        *(int*)(L + 0x8) = *(int*)(L + 0x8) - 8;             // L->top -= 1
        return 0;
    }

    // Fallback: try to set environment via another method
    int result = lua_setFenvFallback();
    if (result != 0) {
        return 0;
    }

    // Error: cannot change environment of given function
    luaL_error(L, "`setfenv' cannot change environment of given function");
    // Trigger a breakpoint (swi 3)
    __asm__ volatile("swi 3");
    return 0;
}