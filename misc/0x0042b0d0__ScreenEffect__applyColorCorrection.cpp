// FUNC_NAME: ScreenEffect::applyColorCorrection
// Function address: 0x0042b0d0
// Applies a color correction/grading effect using lookup tables and clamping.
// Reads global color curve parameters and writes them into a per-effect state.
// Calls virtual methods isActive() (vtable+0x44), update() (vtable+0x18), apply() (vtable+0x1c).
// Uses effectIndex (EAX) to index into global color tables at +0x00e2e620 and +0x00e2e62c.

void ScreenEffect::applyColorCorrection(int effectIndex)
{
    int iVar1;
    undefined4 uVar1, uVar2;
    char cVar3;

    // Read global color tables based on effectIndex
    // g_colorSliderTable1 (0x00e2e620) and g_colorSliderTable2 (0x00e2e62c)
    g_currentColorValue1 = *(int *)(&g_colorSliderTable1 + effectIndex * 4);
    g_currentColorValue2 = *(int *)(&g_colorSliderTable2 + effectIndex * 4);
    g_currentColorValue3 = 0xef - g_currentColorValue2;   // 0xef = 239

    // Clamp global min/max for brightness-like curve
    // g_brightnessMin (0x012058d0), g_brightnessMax (0x00f15988)
    if (g_brightnessMin < 0x16) g_brightnessMin = 0x16;
    if (0x16 < g_brightnessMax) g_brightnessMax = 0x16;
    g_brightnessEnable = 1; // _DAT_011f3a30

    if (g_contrastMin < 0xa8) g_contrastMin = 0xa8;
    if (0xa7 < g_contrastMax) g_contrastMax = 0xa8;
    g_contrastEnable = 0; // _DAT_011f3c78

    if (g_contrastMin < 0xbe) g_contrastMin = 0xbe;
    if (0xbd < g_contrastMax) g_contrastMax = 0xbe;
    g_saturationEnable = 0; // _DAT_011f3cd0

    if (g_brightnessMin < 0x17) g_brightnessMin = 0x17;
    if (0x17 < g_brightnessMax) g_brightnessMax = 0x17;
    g_brightnessStrength = 8; // _DAT_011f3a34

    if (g_brightnessMin < 7) g_brightnessMin = 7;
    if (7 < g_brightnessMax) g_brightnessMax = 7;
    g_gammaEnable = 1; // _DAT_011f39f4

    // Set color channel multipliers
    // g_colorChannelR, G, B, A set to 3,2,1,4
    g_colorChannelR = 3;
    g_colorChannelG = 2;
    g_colorChannelB = 1;
    g_colorChannelA = 4;

    g_colorChannelEnable = 1; // _DAT_011f41f8

    // Check if effect is active (virtual call +0x44)
    cVar3 = (this->vtable->isActive)();
    if (cVar3 == 0) {
        this->vtable->update(); // +0x18
    }

    // Apply color curve using the computed value
    applyColorCurve(g_currentColorValue3); // FUN_0042a720

    // Set RGB multipliers
    setColorMultipliers(g_colorChannelR, g_colorChannelG, g_colorChannelB); // FUN_0041e4d0

    // Set RGBA offsets
    setColorOffsets(g_colorChannelA, g_currentColorValue1, g_currentColorValue2); // FUN_0041e560

    if (g_brightnessMin < 0x34) g_brightnessMin = 0x34;
    if (0x34 < g_brightnessMax) g_brightnessMax = 0x34;
    g_brightnessEnable2 = 1; // _DAT_011f3aa8

    g_colorChannelEnable = 0;
    g_colorChannelEnable2 = 1; // _DAT_011f41d8

    // Allocate and fill a temporary buffer (4 bytes * 8)
    int* tempBuffer = (int*)engineAlloc(0xd, 4, 0, 1, 0); // FUN_0060cd00
    int val1 = g_globalVal1; // 0x00e2eff4
    int val2 = g_globalVal2; // 0x00e2b1a4
    if (tempBuffer != 0) {
        tempBuffer[0] = val1;
        tempBuffer[1] = val2;
        tempBuffer[2] = val2;
        tempBuffer[3] = val2;
        tempBuffer[4] = val2;
        tempBuffer[5] = val1;
        tempBuffer[6] = val1;
        tempBuffer[7] = val1;
        engineFree(); // FUN_0060cde0
    }

    cVar3 = this->vtable->isActive(); // +0x44
    if (cVar3 == 0) {
        this->vtable->applyEffect(); // +0x1c
    }

    // Apply a second effect? Uses a pointer at this+0x4 (a child object?) + offset 0x14
    applyChildEffect(*(int*)(*(int*)((char*)this + 4) + 0x14)); // FUN_0060a460

    // Final clamp/brightness adjustments
    if (g_contrastMin < 0xa8) g_contrastMin = 0xa8;
    if (0xa7 < g_contrastMax) g_contrastMax = 0xa8;
    g_contrastEnable = 0xf;

    if (g_contrastMin < 0xbe) g_contrastMin = 0xbe;
    if (0xbd < g_contrastMax) g_contrastMax = 0xbe;
    g_saturationEnable = 0xf;

    if (g_brightnessMin < 0x17) g_brightnessMin = 0x17;
    if (0x17 < g_brightnessMax) g_brightnessMax = 0x17;
    g_brightnessStrength = 4;

    if (g_brightnessMin < 7) g_brightnessMin = 7;
    g_gammaEnable = 1;
    if (7 < g_brightnessMax) g_brightnessMax = 7;

    return;
}