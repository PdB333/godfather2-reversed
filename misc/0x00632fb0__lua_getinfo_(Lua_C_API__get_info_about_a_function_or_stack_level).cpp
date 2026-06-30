// FUNC_NAME: lua_getinfo (Lua C API: get info about a function or stack level)
int __cdecl lua_getinfo(lua_State* L, const char* what, lua_Debug* ar)
{
    int result = 1;

    if (*what == '>') {
        // '>' modifier: the function to inspect is on top of the stack
        // L->top points to the current top of stack (offset +0x8 in lua_State)
        // Each stack slot is 8 bytes; type tag is stored 8 bytes before the start of the value
        if (*(int*)(*(int*)((char*)L + 8) - 8) != 6) {  // LUA_TFUNCTION = 6
            FUN_00633920(L, "value for `lua_getinfo' is not a function"); // lua_error
        }
        result = FUN_00632e80(L, what + 1, (lua_Debug*)0); // aux_getinfo without debug info
        // Pop the function from stack (decrement top by 8 bytes)
        *(int*)((char*)L + 8) = *(int*)((char*)L + 8) - 8;
    }
    else {
        // Use the supplied lua_Debug structure (third parameter passed in EAX)
        if (*(int*)((char*)ar + 0x5c) == 0) { // ar->i_ci == 0 (likely an "empty" debug record)
            FUN_00632e30(L); // lua_getstack(L, 0) — fill ar with info for current level
        }
        else {
            // ar->i_ci is a valid call info index; compute the associated CallInfo pointer
            // CallInfo size is 0x18 (24 bytes); L->base is at offset +0x28 in lua_State
            CallInfo* ci = (CallInfo*)(*(int*)((char*)L + 0x28) + *(int*)((char*)ar + 0x5c) * 0x18);
            result = FUN_00632e80(L, what, ci);
        }
    }

    // Check for 'f' modifier in 'what' – request to push the function onto the stack
    if (strchr(what, 'f') != (char*)0) {
        // L->stack_last (offset +0x18) - L->top (offset +0x8) must be >= 9 bytes
        if (*(int*)((char*)L + 0x18) - *(int*)((char*)L + 8) < 9) {
            FUN_00635c70(); // luaD_growstack(L) — ensure stack has room
        }
        // Push a slot (8 bytes) onto the stack
        *(int*)((char*)L + 8) = *(int*)((char*)L + 8) + 8;
    }

    return result;
}