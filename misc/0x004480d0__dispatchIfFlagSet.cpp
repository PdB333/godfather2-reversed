// FUNC_NAME: dispatchIfFlagSet

// Function at 0x004480d0: Safe dispatch to a virtual method if a flag is set.
// Checks if 'this' is valid and if a flag at offset 0x14 (this[5]) has bit 0x8000000 set.
// If so, calls virtual function at vtable offset 0x10 (fifth virtual method).
// Otherwise sets *outResult to 0 and returns 0.

uint __thiscall dispatchIfFlagSet(void* this, undefined4 param2, undefined4* outResult)
{
    // this[0] = vtable pointer (int*)
    // this[5] = flags (int) at offset 0x14
    if (this != nullptr && (((int*)this)[5] & 0x8000000U) != 0)
    {
        // Call virtual function at vtable index 4 (offset 0x10)
        return ((uint (__thiscall*)(undefined4, undefined4*))(*(void***)this)[4])(param2, outResult);
    }
    *outResult = 0;
    return 0;
}