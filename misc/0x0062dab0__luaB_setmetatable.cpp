// FUNC_NAME: luaB_setmetatable
// Address: 0x0062dab0
// Role: Implementation of Lua library function setmetatable (sets metatable for table/userdata with protection)
// Based on Lua 5.0 internals (Godfather 2 uses modified Lua)

typedef struct TValue {
    int tt;      // type tag (LUA_TNIL=0, LUA_TTABLE=5, LUA_TUSERDATA=7, etc.)
    void* value; // pointer to actual object (Table, etc.)
} TValue;

typedef struct Table {
    int flags;         // +0x00
    struct Table* metatable;  // +0x04
    int nhash;         // +0x08
    // ... other fields
} Table;

typedef struct global_State {
    // ... 
    int registry; // +0x38? (actually a TValue)
} global_State;

typedef struct lua_State {
    TValue* top;   // +0x08: first free stack slot
    TValue* base;  // +0x0C: base of current function
    global_State* G; // +0x10: pointer to global state
} lua_State;

// External helpers (likely from Lua auxiliary library)
int luaL_checktype(lua_State* L, int narg, int type);  // FUN_00627ac0
int luaL_argerror(lua_State* L, int narg, const char* msg); // FUN_00627a20
int lua_setmetatable(lua_State* L, int objindex);      // FUN_00628120
void lua_error(lua_State* L, const char* msg);         // FUN_00627bd0

// Global string constant
extern const char* table_string; // PTR_s_table_00e2a8b0

int luaB_setmetatable(lua_State* L)
{
    TValue* base = L->base;        // +0x0C
    TValue* top  = L->top;         // +0x08
    TValue* arg1 = base + 2;       // index of second argument? (Lua stacks are 1-based, but internal uses base-relative)
    int ival;

    // --- Check if second argument exists and get its type ---
    // Equivalent to: if (arg1 < top && arg1 != NULL) ival = arg1->tt; else ival = -1;
    if (arg1 < top && arg1 != NULL) {
        ival = arg1->tt;
    } else {
        ival = -1;
    }

    // Convert result from luaL_checktype to handle error (if arg1 is not a table, luaL_typerror will throw)
    // This call expects the first part (high 32 bits) to be the type and low part the index?
    int dummy = luaL_checktype(table_string); // Probably expects (L, 2, LUA_TTABLE) but decompiled shows single arg
    // After call, extraout_ECX might be the new top or similar
    // The decompiled code then uses the low 32 bits as a pointer (piVar1) and high 32 as type
    int type = (int)((unsigned long long)func_result >> 32); // high part
    TValue* obj = (TValue*)func_result; // low part

    // Check that the result object (first argument? actually the table) is of correct type
    if (type != 0 && type != LUA_TTABLE) { // LUA_TTABLE = 5
        luaL_argerror(L, 2, "nil or table expected"); // FUN_00627a20
        // After call, ECX might be updated (extraout_ECX_00)
    }

    // Now check if the object has a protected metatable (__metatable field)
    // obj points to the first argument (table/userdata on stack)
    if (obj < top && obj != NULL) {
        if (obj->tt == LUA_TTABLE || obj->tt == LUA_TUSERDATA) {
            Table* t = (Table*)obj->value;
            int metatableFlags = *(int*)(t + 8); // t->nhash? Actually might be t->metatable->something
            // In Lua, metatable protection: if metatable has __metatable field, error
            if (*(int*)(t + 8) != 0 && *(int*)(t + 8) != *(int*)(L->G + 0x38)) {
                // The metatable's __metatable field is set, so it's protected
                L->base[1] = *(int*)(t + 8); // push protection key? Then set type
                L->base->tt = LUA_TTABLE;
                L->top = L->top + 2; // adjust stack? Actually increments by 2 TValues (8 bytes)
                int result = lua_setmetatable(L); // FUN_00628120 - will detect protection and call error
                if (result != 0) {
                    lua_error(L, "cannot change a protected metatable"); // FUN_00627bd0
                }
            }
        }
    }

    // Clean up stack: pop extra values and set top to base+4 (standard cleanup)
    if ((unsigned int)L->top < (unsigned int)(L->base + 4)) {
        do {
            *(int*)L->top = 0; // set to nil
            L->top = (TValue*)((char*)L->top + 8); // increment by size of TValue
        } while ((unsigned int)L->top < (unsigned int)(L->base + 4));
    }

    // Now restore top to base+4 (should be after cleanup)
    L->top = L->base + 4;

    // If the original first argument was a table or userdata, update its metatable
    TValue* base2 = L->base;
    TValue* arg2 = base2 + 2; // index 2 (the new metatable)
    if (base2->tt == LUA_TTABLE || base2->tt == LUA_TUSERDATA) {
        // Set the metatable's field (or something similar)
        // In Lua, after setmetatable, the metatable is stored in the object's metatable pointer
        // Here it seems to write the new metatable's value into a field at offset +8 of the object
        // This might be the metatable's __metatable field? Or just the metatable pointer.
        // piVar2[1] is the value part of arg2 (the new metatable TValue)
        // It sets it into (object->value + 8)
        *(int*)(((Table*)base2->value) + 8) = arg2->value; // likely sets nhash or metatable pointer?
    }

    L->top = (TValue*)((char*)L->top - 8); // pop one? Actually adjust top back
    return 1; // setmetatable returns the table (or userdata)
}