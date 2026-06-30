// FUNC_NAME: LuaVariableGet
// Address: 0x0046a690
// This function retrieves a game variable by handle and pushes its value onto the Lua stack.
// It is called as a Lua C function (lua_CFunction) with the state as the only parameter.

#include <lua.hpp> // EA's Lua integration

// Forward declarations of game engine functions
// Note: These are reconstructed based on decompilation patterns.
namespace Game {
    extern void* gCoreState; // DAT_01223428, likely a singleton
}

// Simulates lua_getfield(L, LUA_REGISTRYINDEX, "Variable") returning pointer to stored handle.
// Actually returns a pointer to the integer handle value from a registry table.
int* getLuaRegistryHandle(lua_State* L, const char* key) {
    // In reality this would call lua_rawgeti or a custom lookup.
    return nullptr; // Placeholder
}

// Pushes a game variable (identified by its engine pointer) onto the Lua stack.
void pushGameVariableToLuaStack(lua_State* L, void* variablePtr) {
    // Implementation depends on game engine.
}

// Pushes a string onto the Lua stack (wrapper for lua_pushstring).
void luaPushString(lua_State* L, const char* str) {
    lua_pushstring(L, str);
}

// Reports a Lua error and aborts execution.
void luaError(lua_State* L, const char* msg) {
    luaL_error(L, msg);
}

// Invalid variable handle sentinel
const int INVALID_HANDLE = -1;

// The reconstructed function
int LuaVariableGet(lua_State* L) {
    // Get the variable handle from the Lua registry table "Variable".
    // The argument on the stack (index 1) should be a handle number.
    int* handlePtr = reinterpret_cast<int*>(getLuaRegistryHandle(L, "Variable"));
    if (handlePtr != nullptr) {
        int handle = *handlePtr;
        if (handle != INVALID_HANDLE) {
            // Compute the variable object from the game state.
            // gCoreState + 0x24 points to the variable manager array.
            void* coreStatePtr = Game::gCoreState; // DAT_01223428
            int* varManagerArray = *reinterpret_cast<int**>(reinterpret_cast<char*>(coreStatePtr) + 0x24);
            // Each variable entry is 0x14 bytes, offset from base+8.
            void* varPtr = reinterpret_cast<void*>(reinterpret_cast<char*>(varManagerArray) + 8 + handle * 0x14);
            
            // Push the variable value onto the Lua stack.
            pushGameVariableToLuaStack(L, varPtr);

            // Get the variable name string (local_18). It may be stored or passed from Lua.
            const char* varName = nullptr; // In original code, local_18 was uninitialized; likely obtained from Lua stack.
            // If no name, use a default empty string.
            const char* nameToPush = (varName != nullptr) ? varName : &DAT_0120546e; // placeholder for empty string
            
            // Push the variable name as a string (probably for debugging or table key).
            luaPushString(L, nameToPush);
            
            // Cleanup if name was allocated (local_c is destructor).
            if (varName != nullptr) {
                // (*local_c)(local_18); // Typically a free or Lua pop operation
                // In the real code, this might be lua_pop or a custom destructor.
            }
            
            return 1; // One return value on stack (the variable value)
        } else {
            luaError(L, "LuaVariableGet: Invalid variable handle.");
        }
    }
    luaError(L, "LuaVariableGet: Expected variable handle, but found something else.\n");
    // Fallback error trap (swi 3 in original assembly)
    // lua_error(L) would never return, but we include a dummy return.
    return 0;
}