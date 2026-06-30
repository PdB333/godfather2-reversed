// FUNC_NAME: luaReportBadArgument
// Function at 0x00627a20: Lua error reporting for bad arguments (type mismatch).
// Handles both method calls (colon syntax) and regular argument errors.
// Calls a format function and then triggers a debug break (SWI 3).

#include <cstddef>

// Forward declarations of external functions/globals (found in game executable)
extern void __cdecl luaGetFieldOrString(void* L, const char* key);  // FUN_00632fb0 - retrieves a string from Lua state
extern void __cdecl luaPrintf(const char* fmt, ...);               // FUN_00627bd0 - custom printf for error messages

// Global string constants (from .rdata)
extern const char UNKNOWN_STRING_00e4156c[];   // Likely "method" or a key to retrieve function name
extern const char DEFAULT_FUNC_NAME_00e41518[]; // Default function name when none available

void __cdecl luaReportBadArgument(void* L, int argIndex, const char* expectedType) {
    // Retrieve the function name from Lua state (e.g., via lua_tostring or lua_getfield)
    luaGetFieldOrString(L, UNKNOWN_STRING_00e4156c);
    // For simplicity, we assume the retrieved string is stored in a local variable.
    // In the original asm, this pointer is held in a register/stack location.
    const char* funcName; // Actually set by luaGetFieldOrString? The decompiler shows local_64 as separate.
    // The decompiled code compares the retrieved string with "method".
    // We'll simulate by checking if the string equals "method".
    // The original code does a manual 7-byte comparison (including null terminator?).
    bool isMethodCall = (funcName != nullptr && funcName[0] == 'm' && funcName[1] == 'e' && funcName[2] == 't' && 
                         funcName[3] == 'h' && funcName[4] == 'o' && funcName[5] == 'd' && funcName[6] == '\0');

    int adjustedArg = argIndex - 1; // In original, decremented
    if (isMethodCall && adjustedArg == 0) {
        // Specific error for method call on wrong self
        luaPrintf("calling `%s' on bad self (%s)", funcName, expectedType);
    }

    // Fallback: ensure we have a function name, then print standard argument error
    if (funcName == nullptr) {
        funcName = DEFAULT_FUNC_NAME_00e41518;
    }
    luaPrintf("bad argument #%d to `%s' (%s)", argIndex, funcName, expectedType);

    // Trigger debug break (SWI 3) – unrecoverable error
    __asm__ volatile ("swi 3"); // ARM? Actually x86 – but in the x86 binary, it's int3? Original uses swi 3 (software interrupt 3).
    // To match original, we call the breakpoint function via function pointer.
    // In the binary, it's (*(code *)swi(3))(); which is undefined behavior.
    // We replace with __debugbreak() or similar.
    __debugbreak(); // Visual C++ intrinsic for int3
}