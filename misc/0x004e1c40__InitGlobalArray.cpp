// FUNC_NAME: InitGlobalArray
// Initializes a global array of 4 structures (each 0x40 bytes) at 0x01218d40.
// Each structure has a specific pattern: four DWORDs set to g_initSentinel (DAT_00e2b1a4)
// at offsets +0x00, +0x14, +0x28, +0x3c, with the rest zeroed.
// Likely used to reset a pool of objects (e.g., connection slots or controller states).

void InitGlobalArray(void)
{
    // External sentinel value – often 0xFFFFFFFF or a pointer to invalid state
    extern DWORD g_initSentinel; // from DAT_00e2b1a4

    // Array base at 0x01218d40, 4 elements of 0x40 bytes each
    // Each element structure layout (0x40 bytes):
    // +0x00: DWORD m_firstField = g_initSentinel
    // +0x14: DWORD m_secondField = g_initSentinel
    // +0x28: DWORD m_thirdField = g_initSentinel
    // +0x3c: DWORD m_fourthField = g_initSentinel
    // All other fields are zeroed.

    // Element 0 (+0x00)
    *(DWORD*)0x01218d40 = g_initSentinel;
    *(DWORD*)0x01218d44 = 0;
    *(DWORD*)0x01218d48 = 0;
    *(DWORD*)0x01218d4c = 0;
    *(DWORD*)0x01218d50 = 0;
    *(DWORD*)0x01218d54 = g_initSentinel;
    *(DWORD*)0x01218d58 = 0;
    *(DWORD*)0x01218d5c = 0;
    *(DWORD*)0x01218d60 = 0;
    *(DWORD*)0x01218d64 = 0;
    *(DWORD*)0x01218d68 = g_initSentinel;
    *(DWORD*)0x01218d6c = 0;
    *(DWORD*)0x01218d70 = 0;
    *(DWORD*)0x01218d74 = 0;
    *(DWORD*)0x01218d78 = 0;
    *(DWORD*)0x01218d7c = g_initSentinel;

    // Element 1 (+0x40)
    *(DWORD*)0x01218d80 = g_initSentinel;
    *(DWORD*)0x01218d84 = 0;
    *(DWORD*)0x01218d88 = 0;
    *(DWORD*)0x01218d8c = 0;
    *(DWORD*)0x01218d90 = 0;
    *(DWORD*)0x01218d94 = g_initSentinel;
    *(DWORD*)0x01218d98 = 0;
    *(DWORD*)0x01218d9c = 0;
    *(DWORD*)0x01218da0 = 0;
    *(DWORD*)0x01218da4 = 0;
    *(DWORD*)0x01218da8 = g_initSentinel;
    *(DWORD*)0x01218dac = 0;
    *(DWORD*)0x01218db0 = 0;
    *(DWORD*)0x01218db4 = 0;
    *(DWORD*)0x01218db8 = 0;
    *(DWORD*)0x01218dbc = g_initSentinel;

    // Element 2 (+0x80)
    *(DWORD*)0x01218dc0 = g_initSentinel;
    *(DWORD*)0x01218dc4 = 0;
    *(DWORD*)0x01218dc8 = 0;
    *(DWORD*)0x01218dcc = 0;
    *(DWORD*)0x01218dd0 = 0;
    *(DWORD*)0x01218dd4 = g_initSentinel;
    *(DWORD*)0x01218dd8 = 0;
    *(DWORD*)0x01218ddc = 0;
    *(DWORD*)0x01218de0 = 0;
    *(DWORD*)0x01218de4 = 0;
    *(DWORD*)0x01218de8 = g_initSentinel;
    *(DWORD*)0x01218dec = 0;
    *(DWORD*)0x01218df0 = 0;
    *(DWORD*)0x01218df4 = 0;
    *(DWORD*)0x01218df8 = 0;
    *(DWORD*)0x01218dfc = g_initSentinel;

    // Element 3 (+0xc0)
    *(DWORD*)0x01218e00 = g_initSentinel;
    *(DWORD*)0x01218e04 = 0;
    *(DWORD*)0x01218e08 = 0;
    *(DWORD*)0x01218e0c = 0;
    *(DWORD*)0x01218e10 = 0;
    *(DWORD*)0x01218e14 = g_initSentinel;
    *(DWORD*)0x01218e18 = 0;
    *(DWORD*)0x01218e1c = 0;
    *(DWORD*)0x01218e20 = 0;
    *(DWORD*)0x01218e24 = 0;
    *(DWORD*)0x01218e28 = g_initSentinel;
    *(DWORD*)0x01218e2c = 0;
    *(DWORD*)0x01218e30 = 0;
    *(DWORD*)0x01218e34 = 0;
    *(DWORD*)0x01218e38 = 0;
    *(DWORD*)0x01218e3c = g_initSentinel;
}