// FUNC_NAME: GameSettings::initDefaultValues
void __fastcall GameSettings::initDefaultValues(uint32_t* settings)
{
    // Initialize settings block with default values from global constants
    settings[10] = DAT_00d5f7ac;          // +0x28
    settings[11] = DAT_00d5f7a8;          // +0x2C
    settings[12] = DAT_00d5f7a4;          // +0x30
    uint32_t uVar6 = DAT_00e445ac;        // global constant
    uint32_t uVar5 = DAT_00d5f6c0;        // global constant
    uint32_t uVar1 = DAT_00d5d740;        // global constant
    uint32_t uVar2 = _DAT_00d5cf70;       // global constant
    uint32_t uVar3 = DAT_00d5f7a0;        // from earlier
    uint32_t uVar4 = DAT_00d5f37c;        // global constant
    uint32_t uVar7 = DAT_00d5f18c;        // global constant
    uint32_t uVar8 = DAT_00d5efa8;        // global constant
    uint32_t uVar9 = DAT_00d5efa4;        // global constant
    uint32_t uVar10 = DAT_00d5ef90;        // global constant
    uint32_t uVar11 = DAT_00d5ef70;        // global constant
    uint32_t uVar12 = DAT_00d5d7b8;        // global constant
    uint32_t uVar13 = DAT_00d5f79c;        // global constant
    uint32_t uVar14 = DAT_00d5779c;        // global constant
    uint32_t uVar15 = DAT_00d5efd0;        // global constant
    uint32_t uVar16 = _DAT_00d5c458;       // global constant
    uint32_t uVar17 = DAT_00d5eee4;        // global constant
    uint32_t uVar18 = _DAT_00d5780c;       // global constant
    uint32_t uVar19 = DAT_00e44618;        // global constant
    uint32_t uVar20 = DAT_00d5c454;        // global constant

    settings[8] = uVar1;                 // +0x20
    settings[9] = uVar1;                 // +0x24
    settings[13] = uVar3;                // +0x34
    settings[21] = uVar1;                // +0x54
    settings[23] = uVar1;                // +0x5C
    settings[14] = uVar7;                // +0x38
    settings[26] = uVar4;                // +0x68
    settings[15] = uVar8;                // +0x3C
    settings[28] = uVar9;                // +0x70
    settings[17] = uVar10;               // +0x44
    settings[29] = uVar11;               // +0x74
    settings[16] = uVar5;                // +0x40
    settings[20] = uVar12;               // +0x50
    settings[27] = uVar5;                // +0x6C
    settings[30] = uVar13;               // +0x78
    settings[18] = uVar2;                // +0x48
    settings[19] = uVar2;                // +0x4C
    settings[22] = uVar14;               // +0x58
    settings[24] = uVar14;               // +0x60
    settings[31] = uVar16;               // +0x7C
    settings[32] = uVar15;               // +0x80
    settings[33] = uVar15;               // +0x84
    settings[34] = uVar2;                // +0x88
    settings[37] = uVar14;               // +0x94
    settings[40] = uVar16;               // +0xA0
    settings[43] = uVar16;               // +0xAC
    settings[44] = uVar14;               // +0xB0
    settings[46] = uVar16;               // +0xB8
    settings[47] = uVar16;               // +0xBC
    settings[35] = uVar16;               // +0x8C
    settings[0] = 0;                     // +0x00
    settings[1] = 0;                     // +0x04
    *(uint8_t*)(&settings[2]) = 0;       // +0x08 (first byte)
    *(uint8_t*)(&settings[6]) = 0;       // +0x18 (first byte)
    settings[7] = uVar6;                 // +0x1C
    settings[25] = 0;                    // +0x64
    settings[5] = 0;                     // +0x14
    settings[4] = 0;                     // +0x10
    settings[3] = 0;                     // +0x0C
    settings[38] = uVar18;               // +0x98
    settings[39] = uVar6;                // +0x9C
    settings[41] = uVar17;               // +0xA4
    settings[42] = uVar18;               // +0xA8
    settings[45] = uVar19;               // +0xB4
    settings[36] = uVar20;               // +0x90

    return;
}