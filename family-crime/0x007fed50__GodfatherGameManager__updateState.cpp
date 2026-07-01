// FUNC_NAME: GodfatherGameManager::updateState
void __fastcall GodfatherGameManager::updateState(int *thisPtr)
{
    // Write 8-byte value from global at +0x424 (offset 0x109*4)
    *(int64_t *)(thisPtr + 0x109) = DAT_00d71c50;
    // Write 4-byte value from global at +0x42C (offset 0x10b*4)
    thisPtr[0x10b] = DAT_00d71c58;

    // Check flag at +0x8A0 (offset 0x228*4)
    if (thisPtr[0x228] != 0) {
        FUN_007f7a50(); // Possibly a reset or cleanup function
        return;
    }

    // Check flag at +0x3B0 (offset 0xec*4)
    if (thisPtr[0xec] == 0) {
        // Call virtual function at vtable index 0xB7 (0x2dc/4)
        (*(void (**)(void))(*thisPtr + 0x2dc))();
        return;
    }

    // Call external function with globals and the value at +0x3B0
    FUN_00624fa0(DAT_01205224, DAT_012067e8, 0, thisPtr[0xec]);
    // Clear bit 3 (0x8) of flag at +0x894 (offset 0x225*4)
    thisPtr[0x225] &= ~0x8;
}