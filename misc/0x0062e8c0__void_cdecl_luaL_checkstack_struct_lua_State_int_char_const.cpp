// Xbox PDB: void __cdecl luaL_checkstack(struct lua_State *,int,char const *)
// FUNC_NAME: luaB_unpack (Lua base library unpack function)
// This function implements Lua's table.unpack, pushing elements from a table onto the stack.
// Address: 0x0062e8c0

// Lua state struct partial layout (x86 32-bit)
struct lua_State {
    // +0x0: other fields (not used here)
    // +0x8: top - pointer to next free stack slot (TValue*)
    int* top;        // +0x8
    // +0xc: base - pointer to first argument on stack (TValue*)
    int* base;       // +0xc
};

// TValue is 8 bytes (type + value)
struct TValue {
    int value;  // +0x0
    int type;   // +0x4 (type tag, e.g., 5 = LUA_TTABLE)
};

// External function prototypes (assumed from Lua runtime)
extern int luaL_typerror(lua_State* L, int narg, const char* tname);
extern int lua_objlen(lua_State* L, int idx);
extern int lua_checkstack(lua_State* L, int extra);
extern void luaL_error(lua_State* L, const char* fmt, ...);
extern TValue* lua_rawgeti(lua_State* L, int idx, int n); // returns pointer to pushed value

int luaB_unpack(lua_State* L) {
    int* basePtr = L->base;               // pointer to table argument (should be at base + 0? actually base points to first argument)
    int* topPtr = L->top;                 // current stack top

    // Validate that the first argument is a table (type tag 5)
    if ((topPtr <= basePtr) || (basePtr == nullptr) || (*basePtr != 5)) {
        luaL_typerror(L, 1, "table");
    }

    // Get the length of the table (number of elements to unpack)
    int n = lua_objlen(L, 1);             // returns the length of table at index 1

    // Ensure enough stack space for the results
    if (!lua_checkstack(L, n)) {
        luaL_error(L, "stack overflow (%s)", "table too big to unpack");
    }

    // Unpack: push each element onto the stack
    for (int i = 1; i <= n; i++) {
        // Retrieve the i-th element from the table and get a pointer to its TValue
        TValue* src = lua_rawgeti(L, 1, i);

        // Write the TValue to the current top position
        TValue* dest = (TValue*)L->top;
        *dest = *src;                     // copy 8 bytes

        // Advance the top pointer
        L->top = (int*)((char*)L->top + sizeof(TValue));
    }

    return n;  // number of return values left on stack
}