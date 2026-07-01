// FUNC_NAME: getGlobalByteFlag
// Function address: 0x00842870
// Role: Returns a global byte flag (likely a boolean or state indicator) from DAT_012055a1.
// This is a simple getter used by many callers throughout the game code.
unsigned char getGlobalByteFlag(void)
{
    // Global byte at 0x012055a1, likely a debug flag or game state toggle.
    return DAT_012055a1;
}