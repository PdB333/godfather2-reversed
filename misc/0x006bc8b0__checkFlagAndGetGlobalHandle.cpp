// FUNC_NAME: checkFlagAndGetGlobalHandle
// Function at 0x006bc8b0: Returns a handle from a global system if the input flag is non-zero, otherwise returns 0.
// Likely a utility to conditionally access a singleton or system pointer based on a flag.

extern int g_globalData; // DAT_01131040 - global system handle or pointer

// Forward declaration of the internal function that extracts the value
int __cdecl FUN_0043b870(int param);

int __cdecl checkFlagAndGetGlobalHandle(int flag)
{
    if (flag != 0)
    {
        return FUN_0043b870(g_globalData);
    }
    return 0;
}