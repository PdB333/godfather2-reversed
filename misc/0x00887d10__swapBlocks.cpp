// FUNC_NAME: swapBlocks
// Address: 0x00887d10
// Swaps two blocks of memory, each 0x50 bytes (80 bytes = 20 uint32_t values)
void swapBlocks(uint32_t* pData1, uint32_t* pData2) {
    uint32_t temp[20]; // temporary buffer for 20 uint32_t values (0x50 bytes)

    // Copy block 1 to temp
    for (int i = 0; i < 20; i++) {
        temp[i] = pData1[i];
    }

    // Copy block 2 to block 1
    for (int i = 0; i < 20; i++) {
        pData1[i] = pData2[i];
    }

    // Copy temp to block 2
    for (int i = 0; i < 20; i++) {
        pData2[i] = temp[i];
    }
}