// FUNC_NAME: GameConfigManager::parseConfigurationBlocks
// Function address: 0x005684b0
// Reconstructed from Ghidra decompilation
// Purpose: Reads a binary data buffer (+0x350) and extracts configuration name blocks,
// formatting them as "GameConfiguration" or "GameConfiguration<index>" using sprintf.
// The data is tokenized by temporarily null-terminating chunks at computed positions.
// +0x350: char* m_pConfigData (pointer to configuration string buffer)
// +0x354: int m_configDataOffset (current offset/index into buffer)
// +0x08: pointer to a config provider interface (vtable at +0x78 returns a provider object,
// which exposes a method at +0x1c returning the total data/segment length)

void GameConfigManager::parseConfigurationBlocks(void)
{
    char* pData;
    int* pProvider;
    uint totalLen;
    int maxChunkSize;
    char* pCurrent;
    char savedByte;
    uint chunkLen;
    int nameIndex;
    char nameBuffer[32];

    // Obtain a configuration provider object through a virtual call chain
    // The object at +0x08 has a vtable, offset 0x78 returns a pointer to a provider.
    pProvider = (int*)(**(code**)(**(int**)(this + 8) + 0x78))();
    // From that provider, call method at vtable offset 0x1c to get total length of data.
    totalLen = (**(code**)(*pProvider + 0x1c))();

    // Determine the maximum chunk size: if totalLen < 0x41 (65), use totalLen, else 0x40 (64).
    if (totalLen < 0x41) {
        maxChunkSize = (**(code**)(*pProvider + 0x1c))();  // redundant call? possibly gets max boundaries
    } else {
        maxChunkSize = 0x40;
    }

    // Get current buffer pointer and advance the offset by 1.
    pCurrent = *(char**)(this + 0x350);
    totalLen = *(int*)(this + 0x354) + 1;   // Note: original restored as remaining length later

    // If no current buffer, fallback to a static data segment (DAT_0120546e).
    if (pCurrent == (char*)0x0) {
        pCurrent = &DAT_0120546e;
    }

    nameIndex = 0;
    while (true) {
        // Compute the chunk length: min(maxChunkSize-1, totalRemaining)
        // On first iteration, totalLen was just set to original offset+1.
        // This updates on each iteration by subtracting chunkLen.
        chunkLen = maxChunkSize - 1U;
        if (totalLen <= maxChunkSize - 1U) {
            chunkLen = totalLen;
        }

        // Save the byte at the chunk boundary, then null-terminate temporarily.
        savedByte = 0;
        pData = (char*)0x0;
        if (chunkLen < totalLen) {
            savedByte = pCurrent[chunkLen];
            pCurrent[chunkLen] = '\0';      // Temporarily terminate the string
            pData = pCurrent + chunkLen;     // Remember the position for restoration
        }
        pCurrent = pData;   // After processing, move pointer to the null-terminated spot

        // Build the configuration name: first iteration "GameConfiguration", subsequent "GameConfiguration%d"
        if (nameIndex == 0) {
            sprintf(nameBuffer, "GameConfiguration");
        } else {
            sprintf(nameBuffer, "GameConfiguration%d", nameIndex);
        }

        // If no valid chunk (pCurrent null), break out
        if (pCurrent == (char*)0x0) break;

        // Advance remaining length, increment name index
        totalLen = totalLen - chunkLen;
        nameIndex = nameIndex + 1;

        // Restore the saved byte (the delimiter) so the buffer is intact for future iterations
        *pCurrent = savedByte;
    }
    return;
}