// FUNC_NAME: getGameGlobalDouble
// Function address: 0x006d03a0
// Returns a double value from a global variable at 0x00e51120.
// The decompiled output shows a 10-byte x87 extended precision float (float10),
// but likely represents a double in the game's data segment.
double getGameGlobalDouble()
{
    // Global variable storing a double value (x87 extended double in original assembly)
    extern double g_dGameGlobalDouble; // +0x00e51120
    return g_dGameGlobalDouble;
}