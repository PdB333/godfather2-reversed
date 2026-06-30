// FUNC_NAME: StoreSceneState
void StoreSceneState(uint32_t* inputData)
{
    uint32_t tempCopy[32]; // 128 bytes of copied data from inputData
    
    // Copy inputData[0x10..0x1f] first (upper 64 bytes)
    tempCopy[0] = inputData[0x10];
    tempCopy[1] = inputData[0x11];
    tempCopy[2] = inputData[0x12];
    tempCopy[3] = inputData[0x13];
    // inputData[0x14..0x1f] -> tempCopy[4..15] (12 dwords)
    tempCopy[4] = inputData[0x14];
    tempCopy[5] = inputData[0x15];
    tempCopy[6] = inputData[0x16];
    tempCopy[7] = inputData[0x17];
    tempCopy[8] = inputData[0x18];
    tempCopy[9] = inputData[0x19];
    tempCopy[10] = inputData[0x1a];
    tempCopy[11] = inputData[0x1b];
    tempCopy[12] = inputData[0x1c];
    tempCopy[13] = inputData[0x1d];
    tempCopy[14] = inputData[0x1e];
    tempCopy[15] = inputData[0x1f];
    // inputData[0x00..0x0f] -> tempCopy[16..31] (16 dwords)
    tempCopy[16] = inputData[0];
    tempCopy[17] = inputData[1];
    tempCopy[18] = inputData[2];
    tempCopy[19] = inputData[3];
    tempCopy[20] = inputData[4];
    tempCopy[21] = inputData[5];
    tempCopy[22] = inputData[6];
    tempCopy[23] = inputData[7];
    tempCopy[24] = inputData[8];
    tempCopy[25] = inputData[9];
    tempCopy[26] = inputData[10];
    tempCopy[27] = inputData[0xb];
    tempCopy[28] = inputData[0xc];
    tempCopy[29] = inputData[0xd];
    tempCopy[30] = inputData[0xe];
    tempCopy[31] = inputData[0xf];
    
    // Store the original pointer globally (used later?)
    s_inputDataPointer = inputData; // DAT_012054dc
    
    // Call some initialization/processing function with the input data
    ProcessInputData(inputData); // FUN_00423860
    
    // Save a snapshot into a fixed-size buffer (4 slots, each 0xC0 bytes)
    if (s_slotCount < 4) // DAT_01218d30 (number of stored scenes)
    {
        uint32_t* src = tempCopy;
        uint32_t* dst = s_sceneBuffer + s_slotCount * (0xC0 / 4); // DAT_01218a30 + slotIndex * 0xC0 (192 bytes)
        // Copy 0x30 dwords = 192 bytes from local copy to the slot.
        // Note: tempCopy is only 128 bytes, so this reads beyond the valid array!
        // Possibly the loop should be 0x20 (32) dwords, or tempCopy was intended to be larger.
        for (int i = 48; i != 0; i--)
        {
            *dst++ = *src++;
        }
        s_slotCount++; // DAT_01218d30
    }
    
    // Process the copied data locally (maybe display/save)
    ProcessSceneData(tempCopy); // FUN_004e22a0(tempCopy)
    UpdateSceneManager(); // FUN_004e21c0()
    
    // Reset some flags
    s_flagA = 0; // DAT_01194a6c
    s_flagB = 0; // DAT_01194a68
}