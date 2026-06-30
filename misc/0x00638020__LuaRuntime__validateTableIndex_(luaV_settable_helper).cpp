// FUNC_NAME: LuaRuntime::validateTableIndex (luaV_settable helper)
// Address: 0x00638020
// Validates a table key and performs the actual table index operation.
// Handles number and string keys specially; raises Lua errors for nil or NaN indices.
// key is passed in EAX (register); state and table are explicit parameters.
void LuaRuntime::validateTableIndex(lua_State* state, TValue* table, TValue* key) {
    // in_EAX is the key pointer
    TValue* result;
    int type = key->type; // *in_EAX, type tag

    if (type == LUA_TNUMBER) {
        // Check if the number is an integer (no fractional part)
        float f = key->value.f; // in_EAX[1] as float
        if ((float)(int)f != f) {
            goto defaultCase;
        }
        result = (TValue*)luaO_tointeger(state, key); // FUN_00637f10 - convert number to integer index
    } else if (type == LUA_TSTRING) {
        result = (TValue*)luaO_tostring(state, key); // FUN_00637f90 - get string representation
    } else {
defaultCase:
        result = (TValue*)luaT_getmetatable(state, key); // FUN_00637ea0 - get metatable for other types
    }

    // Clear a flag in the table structure (likely rawget flag)
    *(uint8*)((char*)table + 6) = 0; // +0x06: flag byte

    // Check if the result is the nil sentinel (invalid key)
    if (result != &luaO_nilobject) { // &DAT_00e2a93c
        return; // valid key
    }

    // Invalid key: raise appropriate error
    if (type == LUA_TNIL) {
        luaG_runerror(state, "table index is nil"); // FUN_00633920
    } else if (type == LUA_TNUMBER && isnan(key->value.f)) {
        luaG_runerror(state, "table index is NaN");
    }
    // For other invalid types (e.g., function, table), default error is raised elsewhere
    luaH_set(state, table, key); // FUN_00637d60 - set table entry (may also raise)
}