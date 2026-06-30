// FUNC_NAME: UIManager::updateAndRender
// Address: 0x0041faf0
// Role: Updates UI element list, adjusts screen parameters, and renders elements

void UIManager::updateAndRender(void)
{
    uint oldVal1;
    int iVar2;
    uint uVar3;
    uint oldVal2;

    // Save and swap texture/surface slots? (0 and 4)
    oldVal1 = DAT_011f38f4;                 // +0x011f38f4
    oldVal2 = DAT_011f38f0;                 // +0x011f38f0
    DAT_011f38f0 = DAT_01205360;            // +0x01205360
    DAT_011f38f4 = 0;
    FUN_00609340(0, oldVal2, oldVal1);      // Copy or swap surface 0

    oldVal1 = DAT_011f3914;                 // +0x011f3914
    oldVal2 = DAT_011f3910;                 // +0x011f3910
    DAT_011f3910 = DAT_01205364;            // +0x01205364
    DAT_011f3914 = 0;
    FUN_00609340(4, oldVal2, oldVal1);      // Copy or swap surface 4

    // Set up render target? Based on non-zero surface handles
    if (DAT_01205360 == 0) {
        if (DAT_01205364 == 0) goto LAB_0041fb95;
        oldVal2 = 4;
    }
    else {
        oldVal2 = 0;
    }
    FUN_0060db60(oldVal2, 0, 0, 0x3f800000, 0x3f800000);  // Set rect or clear? float 1.0

LAB_0041fb95:
    // Clamp screen dimensions (width/height?) to minimum 0xa8 (168) and 0xbe (190)
    if (DAT_012058d4 < 0xa8) {
        DAT_012058d4 = 0xa8;
    }
    if (0xa7 < DAT_00f1598c) {            // unusual check: if > 0xa7 then set to 0xa8
        DAT_00f1598c = 0xa8;
    }
    _DAT_011f3c78 = 0xf;                  // Set alpha or color component? +0x011f3c78

    if (DAT_012058d4 < 0xbe) {
        DAT_012058d4 = 0xbe;
    }
    if (0xbd < DAT_00f1598c) {
        DAT_00f1598c = 0xbe;
    }
    _DAT_011f3cd0 = 0xf;                  // +0x011f3cd0

    FUN_0041e660(0, 0);                   // Reset or update something
    DAT_01205378 = 0;                     // +0x01205378

    // Iterate over UI element array (elements of size 0x84)
    uint elementIndex = 0;
    if (DAT_01205370 != 0) {              // Number of active elements? +0x01205370
        uint* elementPtr = &DAT_01163820; // Array base
        do {
            // Offset +8: byte indicator; 0 -> 1 iteration, non-zero -> 3 iterations
            int iterations = (*(char*)(elementPtr + 8) != '\0') * 2 + 1;
            for (; iterations != 0; iterations--) {
                uVar3 = 0;
                do {
                    FUN_00434af0();       // Render/animation frame update
                    uVar3++;
                } while (uVar3 < 0x1c);   // 28 calls per iteration
            }
            elementIndex++;
            elementPtr += 0x84 / 4;      // stride 0x84 bytes (0x21 dwords)
        } while (elementIndex < DAT_01205370);
    }
    return;
}