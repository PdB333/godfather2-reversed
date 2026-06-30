// FUNC_NAME: ScriptRuntime::validateTableKey
// Function address: 0x00638020
// Validates a Lua-style table index value. Checks for nil and NaN types.
// If invalid, raises a scripting error and adjusts the stack.

void ScriptRuntime::validateTableKey(lua_State* L, int stackIndex)
{
    // in_EAX: pointer to a Lua value (union of type int and value float/int)
    // *in_EAX is the type tag (0=nil, 3=number, 4=string? etc.)
    int* valuePtr; // passed in EAX (this? or a stack value pointer)
    void* sentinel;
    char* errorMsg;

    // Determine which sentinel to compare based on value type
    if (*valuePtr == 3) // type number
    {
        // Check if the number is not an integer (NaN or non-integer)
        if ((float)(int)*((float*)valuePtr + 1) != *((float*)valuePtr + 1))
        {
            goto genericSentinel;
        }
        sentinel = getNumberSentinel(); // FUN_00637f10
    }
    else if (*valuePtr == 4) // type string? or boolean?
    {
        sentinel = getOtherSentinel(); // FUN_00637f90
    }
    else
    {
genericSentinel:
        sentinel = getGenericSentinel(); // FUN_00637ea0
    }

    // Clear a flag at stackIndex+6 (likely a validity flag in a Lua stack structure)
    *((char*)(stackIndex + 6)) = 0;

    // If the sentinel is not the global nil object, no error
    if (sentinel != &g_globalNil) // DAT_00e2a93c
    {
        return;
    }

    // Determine error message
    if (*valuePtr == 0) // type nil
    {
        errorMsg = "table index is nil";
    }
    else
    {
        // Must be number with NaN value
        if ((*valuePtr != 3) || !isNaN(*((float*)valuePtr + 1)))
        {
            goto done;
        }
        errorMsg = "table index is NaN";
    }

    // Raise the error
    luaError(L, errorMsg); // FUN_00633920

done:
    // Adjust the Lua stack (pop or push)
    adjustStack(L, stackIndex); // FUN_00637d60
}