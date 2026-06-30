// FUNC_NAME: setGlobalDataPair
// Function address: 0x00570950
// Role: Simple setter that stores two 32-bit values into global variables.
// This is likely used for configuration or debug state.
// The global variables gGlobalParam1 and gGlobalParam2 are defined elsewhere.

void setGlobalDataPair(uint param1, uint param2)
{
    // +0x00: gGlobalParam1 (DAT_01205570) - first global value
    // +0x00: gGlobalParam2 (DAT_01205574) - second global value
    gGlobalParam1 = param1;
    gGlobalParam2 = param2;
    return;
}