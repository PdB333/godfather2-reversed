// FUNC_NAME: ParticleManager::spawnParticle
void __thiscall ParticleManager::spawnParticle(int thisPtr, int source, int* flagStruct)
{
    float baseValue = *(float*)(source + 0x18); // +0x18: base intensity
    float scaledValue = (float)*(byte*)(thisPtr + 0x194 + in_EAX) * baseValue; // in_EAX is index (passed in EAX)
    float sumValue = baseValue + scaledValue;

    // One-time initialization of flag
    if (*(char*)(flagStruct + 1) == '\0') {
        FUN_00535450(0, *flagStruct); // Likely a logging or init function
        *(char*)(flagStruct + 1) = 1;
    }

    // Allocate a particle structure (size 5*4? Actually 0x20 dwords = 0x80 bytes)
    int* particle = (int*)FUN_0060cd00(5, 4, 0, 1, 0); // Allocation from pool
    if (particle != nullptr) {
        int globalColor = DAT_00e2b1a4; // Global color or constant
        int zero = 0;
        int globalColor2 = DAT_00e2b1a4;

        FUN_00414aa0(); // Reset or clear something

        // Fill first quad (8 dwords)
        particle[0] = 0;
        particle[1] = 0;
        particle[2] = 0;
        particle[3] = globalColor;
        particle[4] = *(int*)&sumValue; // Store float as int
        particle[5] = zero;
        particle[6] = 0;
        particle[7] = 0;

        FUN_00414aa0();

        // Second quad
        particle[8] = 0;
        particle[9] = 0;
        particle[10] = 0;
        particle[11] = globalColor;
        particle[12] = *(int*)&scaledValue;
        particle[13] = zero;
        particle[14] = 0;
        particle[15] = 0;

        FUN_00414aa0();

        // Third quad
        particle[16] = 0;
        particle[17] = 0;
        particle[18] = 0;
        particle[19] = globalColor;
        particle[20] = *(int*)&sumValue;
        particle[21] = globalColor2;
        particle[22] = 0;
        particle[23] = 0;

        FUN_00414aa0();

        // Fourth quad
        particle[24] = 0;
        particle[25] = 0;
        particle[26] = 0;
        particle[27] = globalColor;
        particle[28] = *(int*)&scaledValue;
        particle[29] = globalColor2;
        particle[30] = 0;
        particle[31] = 0;

        FUN_0060cde0(); // Submit/register particle
    }
}