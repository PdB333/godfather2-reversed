// FUNC_NAME: SomeClass::dispatchConditional
// Function address: 0x005b2b60
// Role: Wrapper that checks if 'this' is valid, then calls an internal target function with an additional flag retrieved from a helper function.
// Purpose: Possibly a dispatch mechanism for events or packets, where the flag indicates whether the object is active.

void __thiscall SomeClass::dispatchConditional(void* thisPtr, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t arg5, uint32_t arg6, uint32_t arg7, uint32_t arg8)
{
    uint32_t flag = 0;
    uint32_t esiValue; // Value held in ESI register, likely set by caller

    if (thisPtr != 0) {
        flag = someFlagFunction(); // FUN_005b2a70
        targetFunction(arg2, arg3, arg4, arg6, arg7, 0, arg8, flag, esiValue, 0);
        return;
    }
    targetFunction(arg2, arg3, arg4, arg6, arg7, 0, arg8, 0, esiValue, 0);
    return;
}