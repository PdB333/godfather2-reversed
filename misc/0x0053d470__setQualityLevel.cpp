// FUNC_NAME: setQualityLevel

void setQualityLevel(float detailLevel, void* param_1)
{
    // Quantize detailLevel to an even integer, clamped to min 2
    uint roundedLevel = (uint)(detailLevel + DAT_00e2b1a4) & 0xfe;
    if (roundedLevel < 2) {
        roundedLevel = 2;
    }

    // Compute table index: ((roundedLevel - 2) >> 1) + 4
    g_ConfigQualityIndex = ((roundedLevel - 2) >> 1) + 4; // +0x28 offset in global struct?

    // Set two values from static data
    g_ConfigLodBias = DAT_01219908;              // +0x5d90? Actually different bases
    g_AnisoFilter = (&g_QualityLevelTable)[g_ConfigQualityIndex * 8]; // +0x5d94? reads first dword of 8-byte entry

    // Store the caller-provided parameter (likely a callback or object pointer)
    g_QualityCallback = param_1;                // +0x5e24

    // Store the final quantized level as float
    g_QualityRounded = (float)roundedLevel;     // +0x6030?
}