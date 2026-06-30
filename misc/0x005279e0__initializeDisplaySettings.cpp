// FUNC_NAME: initializeDisplaySettings
// Function address: 0x005279e0
// Role: Initializes display/color correction settings, allocates a color lookup table, and configures global quality sliders.
// This function appears to be called during game startup to set up user-configurable graphics options (brightness, contrast, saturation, etc.).

// Global variables (renamed for clarity):
extern int g_uiSaturationMax; // DAT_012058d0
extern int g_uiSaturationMin; // DAT_00f15988
extern int g_brightnessSetting; // _DAT_011f3a30
extern int g_contrastSetting; // _DAT_011f39f4
extern int g_saturationSetting; // _DAT_011f3a10
extern int g_gammaSetting; // _DAT_011f3a3c
extern int g_lumaSetting; // _DAT_011f3a38
extern int g_hueSetting; // _DAT_011f3a14
extern int g_sharpnessSetting; // _DAT_011f3a44

extern int g_renderFlags; // DAT_01197d90
extern int g_currentColorCorrectionMode; // DAT_01125ab4
extern int g_colorCorrectionMode1; // DAT_01125b44
extern int g_colorCorrectionMode2; // DAT_01125b48
extern int g_colorCorrectionModeFlag1; // DAT_01125b50
extern int g_colorCorrectionModeFlag2; // DAT_01125b54
extern int g_colorCorrectionParam1; // DAT_01125b5c

extern int g_someGlobalA; // DAT_011f38f0
extern int g_someGlobalB; // DAT_01218e58
extern int g_someFlag; // DAT_011f38f4

// extern unknown buffer base
extern byte g_playerStateArray[0x1000 * 0x38]; // DAT_011a0f28
// offsets: +0x0: state byte, +0x1c: flags uint, +0x10: pointer? (DAT_011a0f44)

extern uint g_colorLUTParam1; // DAT_00e2eff4
extern uint g_colorLUTParam2; // DAT_00e2b1a4

// Forward declarations of called functions:
void FUN_00609890(int param); // unknown
void FUN_0060df60(int a, int b); // unknown
void FUN_00606e60(int ptr, uint flags); // set flags
void FUN_006189c0(); // unknown (reload something)
void FUN_00417cf0(int a, int b, int c); // apply post-processing effect
void FUN_00612a60(); // unknown
void FUN_0053c0c0(); // unknown
void FUN_006063b0(); // unknown
void FUN_0053c250(int a, int b, int c); // unknown
void FUN_0060add0(int a, int b, int* c); // unknown
void* FUN_0060cd00(int size, int align, int flags, int a, int b); // memory allocation
void FUN_0060cde0(); // unknown (free or commit)
void FUN_00612e00(); // unknown

void initDisplaySettings()
{
    int iVar1;
    uint uVar2;
    uint uVar3;
    uint *puVar4;

    // First check: if the two globals match and a flag is zero, call a simple init; otherwise complex init.
    if ((g_someGlobalA == g_someGlobalB) && (g_someFlag == 0)) {
        FUN_00609890(1);
    } else {
        FUN_0060df60(g_someGlobalA, g_someGlobalB);
    }

    // If the second global is a valid index (< 0x1000), update a player state entry.
    if ((g_someGlobalB != 0xffffffff) && (g_someGlobalB < 0x1000)) {
        iVar1 = g_someGlobalB * 0x38;
        if ((&g_playerStateArray[0] + iVar1 != (byte *)0x0) && ((byte)(&g_playerStateArray[0])[iVar1] < 4)) {
            // Check if there's a pointer at +0x10 (relative to entry)
            if (*(int *)(&g_playerStateArray[0x1c] + iVar1) != 0) { // assuming +0x1c for the pointer field
                FUN_00606e60(*(int *)(&g_playerStateArray[0x1c] + iVar1), 0x200000);
            }
            // Set flags at +0x0c (assuming offset)
            *(uint *)(&g_playerStateArray[0x0c] + iVar1) = *(uint *)(&g_playerStateArray[0x0c] + iVar1) & 0xfcac8fff | 0x200000;
            FUN_006189c0();
        }
    }

    // --- Set brightness (index 0x16 = 22) ---
    // Clamp g_uiSaturationMax and g_uiSaturationMin to range [0x16, 0x16] (just ensure max >= min)
    if (g_uiSaturationMax < 0x16) {
        g_uiSaturationMax = 0x16;
    }
    if (0x16 < g_uiSaturationMin) {
        g_uiSaturationMin = 0x16;
    }
    g_brightnessSetting = 1;

    // --- Set contrast (index 7) ---
    if (g_uiSaturationMax < 7) {
        g_uiSaturationMax = 7;
    }
    if (7 < g_uiSaturationMin) {
        g_uiSaturationMin = 7;
    }
    g_contrastSetting = 0;

    // --- Set saturation (index 0xe = 14) ---
    if (g_uiSaturationMax < 0xe) {
        g_uiSaturationMax = 0xe;
    }
    if (0xe < g_uiSaturationMin) {
        g_uiSaturationMin = 0xe;
    }
    g_saturationSetting = 0;

    // --- Set gamma (index 0x19 = 25) ---
    if (g_uiSaturationMax < 0x19) {
        g_uiSaturationMax = 0x19;
    }
    if (0x19 < g_uiSaturationMin) {
        g_uiSaturationMin = 0x19;
    }
    g_gammaSetting = 5;

    // --- Set luma (index 0x18 = 24) ---
    if (g_uiSaturationMax < 0x18) {
        g_uiSaturationMax = 0x18;
    }
    if (0x18 < g_uiSaturationMin) {
        g_uiSaturationMin = 0x18;
    }
    g_lumaSetting = 0;

    // --- Set hue (index 0xf = 15) ---
    if (g_uiSaturationMax < 0xf) {
        g_uiSaturationMax = 0xf;
    }
    if (0xf < g_uiSaturationMin) {
        g_uiSaturationMin = 0xf;
    }
    g_hueSetting = 0;

    // --- Set sharpness (index 0x1b = 27) ---
    if (g_uiSaturationMax < 0x1b) {
        g_uiSaturationMax = 0x1b;
    }
    if (0x1a < g_uiSaturationMin) { // note: uses 0x1a but then assigns 0x1b (probably a bug or intended)
        g_uiSaturationMin = 0x1b;
    }
    g_sharpnessSetting = 0;

    // Apply first effect (effect type 1, sub-type 2, strength 1)
    FUN_00417cf0(1, 2, 1);

    // Determine color correction mode based on render flags
    if ((g_renderFlags & 0x400000) == 0) {
        g_currentColorCorrectionMode = g_colorCorrectionMode2; // default mode
    } else {
        g_currentColorCorrectionMode = g_colorCorrectionMode1; // alternative mode
    }

    FUN_00612a60();
    FUN_0053c0c0();

    // If using alternative mode, check and apply additional color correction flags
    if (g_currentColorCorrectionMode == g_colorCorrectionMode1) {
        if (g_colorCorrectionModeFlag1 != 0) {
            FUN_006063b0();
        }
        if ((g_currentColorCorrectionMode == g_colorCorrectionMode1) && (g_colorCorrectionModeFlag2 != 0)) {
            FUN_006063b0();
        }
    }

    // Set some rendering parameters (likely gamma/color)
    FUN_0053c250(g_renderFlags, /* unknown */, /* unknown */);

    // If using alternative mode, apply another color correction function with additional parameters
    if (g_currentColorCorrectionMode == g_colorCorrectionMode1) {
        FUN_0060add0(g_currentColorCorrectionMode, g_colorCorrectionParam1, &g_renderFlags);
    }

    // Allocate a buffer (size = 0xd * 4 = 52 bytes? Actually 0xd in units of 4? But parameters: 0xd,4,0,1,0)
    puVar4 = (uint *)FUN_0060cd00(0xd, 4, 0, 1, 0); // alloc 0xd * 4 = 52 bytes, alignment 4
    uVar3 = g_colorLUTParam1;
    uVar2 = g_colorLUTParam2;
    if (puVar4 != (uint *)0x0) {
        // Fill the buffer with color lookup table data (16 uint32 values)
        puVar4[0] = g_colorLUTParam1;      // some base value
        puVar4[1] = uVar2;                // repeated param2
        puVar4[2] = 0;
        puVar4[3] = 0;
        puVar4[4] = uVar2;
        puVar4[5] = uVar2;
        puVar4[6] = uVar2;
        puVar4[7] = 0;
        puVar4[8] = uVar2;
        puVar4[9] = uVar3;
        puVar4[10] = uVar2;
        puVar4[11] = uVar2;
        puVar4[12] = uVar3;
        puVar4[13] = uVar3;
        puVar4[14] = 0;
        puVar4[15] = uVar2;
        FUN_0060cde0(); // probably commit the allocation
    }

    FUN_00612e00(); // finalize the color correction setup

    // --- Repeat the clamping and default setting (maybe to ensure consistency) ---
    if (g_uiSaturationMax < 0x16) {
        g_uiSaturationMax = 0x16;
    }
    if (0x16 < g_uiSaturationMin) {
        g_uiSaturationMin = 0x16;
    }
    g_brightnessSetting = 1;

    if (g_uiSaturationMax < 7) {
        g_uiSaturationMax = 7;
    }
    if (7 < g_uiSaturationMin) {
        g_uiSaturationMin = 7;
    }
    g_contrastSetting = 1; // note: changed from 0 to 1 after second pass

    if (g_uiSaturationMax < 0xe) {
        g_uiSaturationMax = 0xe;
    }
    if (0xe < g_uiSaturationMin) {
        g_uiSaturationMin = 0xe;
    }
    g_saturationSetting = 1; // changed from 0 to 1

    if (g_uiSaturationMax < 0x19) {
        g_uiSaturationMax = 0x19;
    }
    if (0x19 < g_uiSaturationMin) {
        g_uiSaturationMin = 0x19;
    }
    g_gammaSetting = 7; // changed from 5 to 7

    if (g_uiSaturationMax < 0x18) {
        g_uiSaturationMax = 0x18;
    }
    if (0x18 < g_uiSaturationMin) {
        g_uiSaturationMin = 0x18;
    }
    g_lumaSetting = 0; // unchanged

    if (g_uiSaturationMax < 0xf) {
        g_uiSaturationMax = 0xf;
    }
    if (0xf < g_uiSaturationMin) {
        g_uiSaturationMin = 0xf;
    }
    g_hueSetting = 0; // unchanged

    if (g_uiSaturationMax < 0x1b) {
        g_uiSaturationMax = 0x1b;
    }
    if (0x1a < g_uiSaturationMin) {
        g_uiSaturationMin = 0x1b;
    }
    g_sharpnessSetting = 0; // unchanged

    // Apply second effect (effect type 1, sub-type 5, strength 6)
    FUN_00417cf0(1, 5, 6);
}