// FUNC_NAME: initGameSystems
void __cdecl initGameSystems(/* implicit ESI parameter? */ unsigned int param_esi)
{
    // Temporary structure for initializing global data
    unsigned int dataPtr;
    unsigned int zero1;
    unsigned char zero2;

    // Initialize first global data structure (DAT_0120e978) to zero
    dataPtr = (unsigned int)DAT_0120e978;  // +0x0: pointer to global data
    zero1 = 0;                              // +0x4: zero
    zero2 = 0;                              // +0x8: zero byte
    FUN_00408a00(&dataPtr, 0);              // Likely memset or struct init

    // Call next initialization functions (possibly systems)
    FUN_004540f0(param_esi);                // ESI is passed through, could be game instance
    FUN_00655670();                         // High address, maybe a plugin or engine system
    FUN_006555b0();
    FUN_00453f70();                         // Nearby function

    // Initialize second global data structure (DAT_0120ea74) to zero
    dataPtr = (unsigned int)DAT_0120ea74;
    zero1 = 0;
    zero2 = 0;
    FUN_00408a00(&dataPtr, 0);
    return;
}