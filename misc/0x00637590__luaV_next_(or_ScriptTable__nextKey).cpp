// FUNC_NAME: luaV_next (or ScriptTable::nextKey)
// Address: 0x00637590
// Purpose: Implements Lua 'next' function for iterating over tables.
//          Given a key (via 'this' pointer) and a table, returns the next key index (0-based).
//          Handles integer keys (array part) and other types (hash part).

#include <cstdint>

// Forward declarations for internal functions
void* __cdecl getHashNodeForFloatKey(void);
void* __cdecl getHashNodeForStringKey(void);
void* __cdecl getHashNodeDefault(void);
void __cdecl reportLuaError(void* luaState, const char* msg);

// Global nil sentinel (address from DAT_00e2a93c)
const void* LUA_NIL_SENTINEL = reinterpret_cast<const void*>(0x00e2a93c);

// Lua value type tags (first field of a Lua value object)
enum LuaType : int32_t {
    LUA_TNIL        = 0,
    LUA_TNUMBER     = 3,   // float representation of integer
    LUA_TSTRING     = 4,   // or other types
    // ... others not used here
};

// Lua value object (stack representation or generic key)
struct LuaValue {
    int32_t  type;          // +0x00 type tag
    float    value_float;   // +0x04 actual value (for numbers) or pointer for strings
    // ...
};

// Table structure (partial)
struct LuaTable {
    void*    array_base;    // +0x10 pointer to start of array part
    int32_t  array_size;    // +0x1c number of elements in array part
    // likely hash part fields follow
};

// __thiscall: 'this' points to the current key (LuaValue*)
uint32_t __thiscall luaV_next(void* luaState, int32_t table) {
    LuaValue* key = reinterpret_cast<LuaValue*>(this);
    LuaTable* tbl = reinterpret_cast<LuaTable*>(table);

    // Check for nil key -> end of iteration
    if (key->type == LUA_TNIL) {
        return 0xFFFFFFFF;
    }

    // Handle integer keys (array part)
    if (key->type == LUA_TNUMBER) {
        int32_t intVal = static_cast<int32_t>(key->value_float);
        // Verify that the float exactly represents an integer and is positive
        if (static_cast<float>(intVal) == key->value_float && intVal > 0) {
            // The key is a valid integer. Check if it falls within array bounds.
            // The original condition: (intVal-1 & 0xff000000) == 0 ensures high byte is zero? 
            // Probably just checks that the index is not too large.
            if (intVal <= tbl->array_size) {
                // Return 0-based index (Lua 1-based -> C 0-based)
                return intVal - 1;
            }
        }
        // If not a valid array index, fall through to hash part
    }

    // For non-integer keys, look up in hash part
    void* node;
    if (key->type == LUA_TNUMBER) {
        node = getHashNodeForFloatKey();
    } else if (key->type == LUA_TSTRING) {
        node = getHashNodeForStringKey();
    } else {
        node = getHashNodeDefault();
    }

    // Check if the key is actually present
    if (node == LUA_NIL_SENTINEL) {
        reportLuaError(luaState, "invalid key for `next'");
        // In Lua, this would be an error; here we just return something
    }

    // Convert hash node address to an index
    // The hash nodes are stored in an array of 20-byte structures.
    // Each node is referenced by its key field, which is 8 bytes before the start of the structure.
    // Index = ((node - 8 - array_base) / 20) + array_size
    // This yields an index that continues from the array part (array_size offset).
    intptr_t offset = reinterpret_cast<intptr_t>(node) - 8 - reinterpret_cast<intptr_t>(tbl->array_base);
    uint32_t index = static_cast<uint32_t>(offset / 20) + tbl->array_size;
    return index;
}