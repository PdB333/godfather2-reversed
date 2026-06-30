// FUNC_NAME: DebugValidateStructMagic

void DebugValidateStructMagic(int* pStruct, unsigned int param2)
{
    // Magic constants for structure identification (debug check)
    // These likely serve as a cookie to verify that the pointer points to a valid object of expected type.
    const int magic0 = 0xBABDBDBA;
    const int magic1 = 0xBEEFBEEF;
    const int magic2 = 0xEAC15A55;
    const int magic3 = 0x91100911;

    // Check if the first four dwords match the magic or are all zero (uninitialized/cleared).
    bool magicMatch = (pStruct[0] == magic0 && pStruct[1] == magic1 &&
                       pStruct[2] == magic2 && pStruct[3] == magic3);
    bool allZero   = (pStruct[0] == 0 && pStruct[1] == 0 &&
                      pStruct[2] == 0 && pStruct[3] == 0);

    if (!magicMatch && !allZero)
    {
        // Invalid structure: trigger debug failure / assertion.
        // The function at 0x00856780 likely displays an error or breaks into the debugger.
        FUN_00856780(pStruct, param2, 0, 0, 1);
    }
}