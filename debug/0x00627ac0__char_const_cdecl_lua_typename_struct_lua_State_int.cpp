// Xbox PDB: char const * __cdecl lua_typename(struct lua_State *,int)
// FUNC_NAME: Debug::typeCheckAssert
// Function at 0x00627ac0: Type assertion failure handler - prints expected vs actual value string, then aborts.
// Called from many type-checking sites across the codebase.
// Uses a global string table (PTR_DAT_00e2a89c) to resolve value IDs to names.
void Debug::typeCheckAssert(const char* expectedTypeStr) {
    // unaff_EDI is a loop counter or index from caller (likely an iterator over a container)
    // in_EAX is a "this" pointer to some container or state object
    int* valuePtr = nullptr;
    const char* actualTypeStr = "no value";

    if (unaff_EDI < 1) {
        // No valid iterator offset; try to get current value from a static getter
        valuePtr = (int*)FUN_00625430(); // Likely returns pointer to internal value table or current value
    }
    else {
        // Use iterator: structure at in_EAX has a pointer to current element
        // +0x0c: pointer to array of elements? -8 + index*8
        // +0x08: end pointer of the array
        valuePtr = (int*)(*(int*)(in_EAX + 0xc) - 8 + unaff_EDI * 8);
        if (valuePtr < *(int**)(in_EAX + 8)) {
            goto checkValue;
        }
        // If out of bounds, fall through to "no value"
    }

checkValue:
    if (valuePtr != nullptr && *valuePtr != -1) {
        // Use the value as index into the global string table (PTR_DAT_00e2a89c)
        actualTypeStr = (&PTR_DAT_00e2a89c)[*valuePtr]; // Array of const char*
    }

    // Print error message: "expected <expectedTypeStr>, got <actualTypeStr>"
    FUN_00625d40("%s expected, got %s", expectedTypeStr, actualTypeStr);

    // Call assertion abort handler
    FUN_00627a20(); // Likely triggers a breakpoint or abort

    // Force a breakpoint via software interrupt
    // This is a debug trap (int 3 or similar)
    ((void (*)())0x3)(); // Or just __debugbreak(); in MSVC
    return;
}