// Xbox PDB: int __cdecl luaL_argerror(struct lua_State *,int,char const *)
// FUNC_NAME: luaErrorHandler
// Address: 0x00627a20
// Role: Lua error/panic handler - prints error message and triggers debug break

#include <cstdarg>

// Forward declarations - these would be in the EARS Lua implementation
const char* getLuaStringFromState(void* L, const char* key);
void luaPrintf(const char* format, ...); // Actually FUN_00627bd0 which is printf-like

// Global string constants (from data section)
// DAT_00e4156c - likely a key like "method" or something
// DAT_00e41518 - default string like "unknown"

void __cdecl luaErrorHandler(void* L, int argIndex, const char* errorMsg)
{
    const char* methodName;
    const char* defaultName;
    const char* compareStr;
    bool isMethod;
    int i;

    // Get the method name from the Lua state (param_1 is the state)
    methodName = getLuaStringFromState(L, g_methodKey); // DAT_00e4156c

    // Check if the caller is a method by comparing string to "method"
    compareStr = "method";
    i = 7; // length of "method"+1?
    isMethod = true;
    do {
        if (i == 0) break;
        i--;
        if (*methodName != *compareStr) {
            isMethod = false;
            break;
        }
        methodName++;
        compareStr++;
    } while (isMethod);

    if (isMethod && (argIndex--, argIndex == 0)) {
        // Report "calling `%s' on bad self (%s)"
        luaPrintf("calling `%s' on bad self (%s)", methodName, errorMsg);
    }

    // Ensure we have a default string for the argument name
    if (methodName == nullptr) {
        methodName = g_defaultArgName; // DAT_00e41518
    }

    // Report "bad argument #%d to `%s' (%s)"
    luaPrintf("bad argument #%d to `%s' (%s)", argIndex, methodName, errorMsg);

    // Trigger a debug break / crash
    __debugbreak(); // swi(3) on ARM; on x86 this would be int3
}