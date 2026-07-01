// FUNC_NAME: getGlobalByteFlag
bool getGlobalByteFlag(void)
{
    // Returns the value of a global byte flag at 0x012055a2.
    // Used by multiple callers (0x006f3e10, 0x006f1ed0, etc.) for state checks.
    return DAT_012055a2;
}