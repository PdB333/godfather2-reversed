// FUNC_NAME: clearGlobalStateFlags
// Function address: 0x0048fc00
// Role: Resets two global status flags to zero. Likely called during initialization or state reset.
// The flags are consecutive bytes at 0x012053da and 0x012053db.

extern unsigned char g_globalFlagA; // 0x012053da
extern unsigned char g_globalFlagB; // 0x012053db

void clearGlobalStateFlags(void)
{
    g_globalFlagA = 0;
    g_globalFlagB = 0;
}