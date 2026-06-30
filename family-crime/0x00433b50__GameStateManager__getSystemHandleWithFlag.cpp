// FUNC_NAME: GameStateManager::getSystemHandleWithFlag
uint GameStateManager::getSystemHandleWithFlag(void) {
    int *pData;       // Retrieved pointer from manager offset +4
    uint high24Bits;  // Upper 24 bits of pData (shifted right by 8)

    // Get pointer from the game manager structure (offset +0x4)
    pData = *(int **)(*(uintptr*)g_pGameStateManager + 4);

    // Check bit 4 of field at offset 0xebe (0x3AF8 bytes) in the pointed structure
    if ((((uint)pData[0xebe] >> 4) & 1) == 0) {
        // Bit not set → return pData with its low byte cleared (handle without generation/flag)
        return (uint)pData & 0xFFFFFF00;
    }

    // Bit set → extract upper 24 bits of pData as a handle index
    high24Bits = (uint)pData >> 8;

    // Check if the element at index (*pData + 14) is zero
    if (pData[*pData + 0xe] == 0) {
        // Element zero → return (high24Bits << 8) | 1 (low byte = 1)
        return CONCAT31(high24Bits, 1);
    }

    // Otherwise check element at index ((*pData - 1) & 3) + 14
    return CONCAT31(high24Bits, pData[(*pData - 1U & 3) + 0xe] == 0);
}