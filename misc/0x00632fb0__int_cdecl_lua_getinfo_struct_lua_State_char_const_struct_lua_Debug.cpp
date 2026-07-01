// Xbox PDB: int __cdecl lua_getinfo(struct lua_State *,char const *,struct lua_Debug *)
// FUNC_NAME: lua_getinfo
// Address: 0x00632fb0
// Implementation of lua_getinfo with support for '>' option and 'f' option stack expansion

int lua_getinfo(lua_State* L, const char* what)
{
    int result = 1; // default return value (success)

    if (*what == '>') {
        // Handle the '>' prefix: function index provided at top of stack
        int stackTop = *(int*)(*(int*)(L + 8) - 8); // L->top->tt (type tag)
        if (stackTop != 6) { // LUA_TFUNCTION
            lua_error(L, "value for `lua_getinfo' is not a function");
        }
        result = lua_getinfo_inner(L, what + 1, 0); // level 0
        // Pop the function from stack (each slot is 8 bytes)
        *(int*)(L + 8) = *(int*)(L + 8) - 8; // L->top -= 1
    }
    else {
        // No '>': use current activation record
        // Register variable holding current function/closure pointer (from EAX)
        void* currentFunc = (void*)in_EAX; // passed in register, holds L->ci or similar
        if (*(int*)(currentFunc + 0x5c) == 0) {
            lua_getstack_default(L);
        }
        else {
            int stackPos = *(int*)(L + 0x28) + *(int*)(currentFunc + 0x5c) * 0x18;
            result = lua_getinfo_inner(L, what, stackPos);
        }
    }

    // Check for 'f' option: push function onto stack
    char* fPos = _strchr(what, 'f');
    if (fPos != NULL) {
        // Ensure stack has room for one TValue (8 bytes)
        if (*(int*)(L + 0x18) - *(int*)(L + 8) < 9) { // .stacksize - .top < 1
            lua_expand_stack(); // grow stack
        }
        *(int*)(L + 8) = *(int*)(L + 8) + 8; // L->top += 1
    }

    return result;
}