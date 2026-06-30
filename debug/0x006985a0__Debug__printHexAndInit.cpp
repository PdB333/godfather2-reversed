// FUNC_NAME: Debug::printHexAndInit
int __thiscall Debug::printHexAndInit(int this, uint hexValue)
{
    int i;
    // Print 8 hex digits of the value (e.g., for debug ID display)
    for (i = 8; i > 0; i--)
    {
        char digit = "0123456789ABCDEF"[hexValue & 0xF];
        debugOutputChar(digit); // FUN_004d4150 - output single character
        hexValue >>= 4;
    }
    // Clear field at +0x0C (likely a flag or state)
    *(int*)(this + 0xC) = 0;
    // Register/log with global data (DAT_00d5ce30, type 2, sub 0, flags 0)
    debugRegister(&DAT_00d5ce30, 2, 0, 0); // FUN_004d3ca0
    return this;
}