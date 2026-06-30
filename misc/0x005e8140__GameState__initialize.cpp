// FUNC_NAME: GameState::initialize
undefined4 * __fastcall GameState::initialize(undefined4 *thisPtr)
{
    // thisPtr is a pointer to a large structure (at least 0x129 dwords = 0x4A4 bytes)
    // Offset 0x000: first dword set to 0
    thisPtr[0] = 0;

    // Loop 4 times (i = 3 down to 0) to initialize 4 player slots (each 108 bytes = 0x1B dwords)
    int *puVar2 = (int *)thisPtr + 1; // Offset +0x004
    int *puVar1 = (int *)thisPtr + 7; // Offset +0x01C
    int iteration = 3;
    do {
        *puVar2 = 0;                                     // +0x004 + i*108
        puVar1[-5] = 0; puVar1[-4] = 0; puVar1[-3] = 0; // +0x008..+0x014
        puVar1[-2] = 0; puVar1[-1] = 0; *puVar1 = 0;    // +0x014..+0x01C
        puVar1[1] = 0; puVar1[2] = 0; puVar1[3] = 0;    // +0x020..+0x028
        puVar1[4] = 0; puVar1[5] = 0; puVar1[6] = 0;    // +0x02C..+0x034
        puVar1[7] = 0; puVar1[8] = 0; puVar1[9] = 0;    // +0x038..+0x044
        puVar1[10] = 0; puVar1[11] = 0;                  // +0x048..+0x04C
        puVar1[12] = 0; puVar1[13] = 0;                  // +0x050..+0x054
        // Note: 20 dwords zeroed per iteration (including *puVar2)
        // Stride is 0x1B dwords = 108 bytes between slots

        puVar2 += 0x1B;
        puVar1 += 0x1B;
        iteration--;
    } while (iteration >= 0);

    // Call secondary initialization routine
    GameState::initSecondary((undefined4 *)thisPtr); // FUN_005e7db0

    // Set additional fields at offsets +0x494, +0x498, +0x49C, +0x4A0 to 0
    thisPtr[0x125] = 0;
    thisPtr[0x126] = 0;
    thisPtr[0x127] = 0;
    thisPtr[0x128] = 0;

    return thisPtr;
}