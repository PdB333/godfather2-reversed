// FUNC_NAME: setGlobalParameter
// Function address: 0x0060e890
// Stores a 32-bit value to a global variable (DAT_012058c0), likely a game setting or debug flag.
void __cdecl setGlobalParameter(int param)
{
    DAT_012058c0 = param;
}