// FUNC_NAME: InputManager::storeSnapshot
void InputManager::storeSnapshot(uint32_t *pState) {
    uint32_t buffer[48]; // Local buffer (192 bytes total)

    // Copy state data into local buffer with halves swapped
    // High half (offset 0x10..0x1f) goes to low addresses
    buffer[0] = pState[0x10];
    buffer[1] = pState[0x11];
    buffer[2] = pState[0x12];
    buffer[3] = pState[0x13];
    buffer[4] = pState[0x14];  // local_c0
    buffer[5] = pState[0x15];  // uStack_bc
    buffer[6] = pState[0x16];  // uStack_b8
    buffer[7] = pState[0x17];  // uStack_b4
    buffer[8] = pState[0x18];  // local_b0
    buffer[9] = pState[0x19];  // uStack_ac
    buffer[10] = pState[0x1a]; // uStack_a8
    buffer[11] = pState[0x1b]; // uStack_a4
    buffer[12] = pState[0x1c]; // local_a0
    buffer[13] = pState[0x1d]; // uStack_9c
    buffer[14] = pState[0x1e]; // uStack_98
    buffer[15] = pState[0x1f]; // uStack_94
    // Low half (offset 0x00..0x0f) goes to higher addresses
    buffer[16] = pState[0x00]; // local_90
    buffer[17] = pState[0x01]; // uStack_8c
    buffer[18] = pState[0x02]; // uStack_88
    buffer[19] = pState[0x03]; // uStack_84
    buffer[20] = pState[0x04]; // local_80
    buffer[21] = pState[0x05]; // uStack_7c
    buffer[22] = pState[0x06]; // uStack_78
    buffer[23] = pState[0x07]; // uStack_74
    buffer[24] = pState[0x08]; // local_70
    buffer[25] = pState[0x09]; // uStack_6c
    buffer[26] = pState[0x0a]; // uStack_68
    buffer[27] = pState[0x0b]; // uStack_64
    buffer[28] = pState[0x0c]; // local_60
    buffer[29] = pState[0x0d]; // uStack_5c
    buffer[30] = pState[0x0e]; // uStack_58
    buffer[31] = pState[0x0f]; // uStack_54

    // Global pointer to the current state block
    g_pCurrentSnapshot = pState; // 0x012054dc

    // Initialize the system with the state pointer
    initialiseSystem(pState); // FUN_00423860

    // Write this snapshot into the history buffer if there's room
    if (g_snapshotCount < 4) { // 0x01218d30
        uint32_t *pDest = &g_snapshotHistory[g_snapshotCount][0]; // 0x01218a30 + count * 0xc0
        for (int i = 0; i < 48; ++i) {
            pDest[i] = buffer[i];
        }
        g_snapshotCount++; // 0x01218d30
    }

    // Additional system update functions
    processSnapshot(buffer); // FUN_004e22a0
    resetSystem();           // FUN_004e21c0

    // Reset flags
    g_inputFlag1 = 0; // 0x01194a6c
    g_inputFlag2 = 0; // 0x01194a68
}