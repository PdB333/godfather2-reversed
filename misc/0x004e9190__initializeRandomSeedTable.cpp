// FUNC_NAME: initializeRandomSeedTable

void initializeRandomSeedTable(void)
{
    uint32_t seed = 0xDECAFBAD;
    uint32_t temp;
    uint32_t* tablePtr = &g_randomSeedTable[0];
    uint32_t count = 20; // 0x14

    g_rngSeed = 0xDECAFBAD;
    g_rngTableCount = 20;

    do {
        // Linear congruential generator: multiply by 0x41A7 with 32-bit wrapping
        // Break into high/low to simulate 32-bit multiplication (common in EARS engine)
        temp = (g_rngSeed >> 16) * 0x41A7;
        seed = (seed & 0xFFFF) * 0x41A7 + (temp & 0x7FFF) * 0x10000 + (temp >> 15);
        if ((int32_t)seed < 0) {
            seed += 0x80000001; // Compensate for signed overflow
        }
        g_rngSeed = seed;
        *tablePtr = seed;
        tablePtr++;
    } while ((int32_t)tablePtr < (int32_t)&g_randomSeedTable[count]);
}