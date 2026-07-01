//FUNC_NAME: GameConfig::initializeDefaults

void __thiscall GameConfig::initializeDefaults(GameConfig* thisConfig)
{
    // Load default values from global constants
    // Offsets are in 4-byte units (index * 4)
    thisConfig->field_0x38 = DAT_00d5780c;   // +0x38
    thisConfig->field_0x3c = DAT_00e445ac;    // +0x3c
    thisConfig->field_0x40 = DAT_00d5780c;    // +0x40
    thisConfig->field_0x44 = DAT_00e445ac;    // +0x44
    thisConfig->field_0x50 = DAT_00d5c458;    // +0x50 (index 0x14? Wait careful)
    // Actually indices: param_1[0] = +0x00, param_1[1] = +0x04, etc.
    // Let's map all assignments with correct offsets.

    // Reconstructing from the decompiled code:
    // param_1[0xe] = DAT_00d5f6c4;  // +0x38
    // param_1[0xf] = DAT_00d5fb68;  // +0x3c
    // param_1[0x10] = uVar6;        // +0x40
    // param_1[0x11] = DAT_00d6ef5c; // +0x44
    // param_1[0x18] = uVar5;        // +0x60
    // param_1[0x19] = uVar5;        // +0x64
    // param_1[0xd] = uVar1;         // +0x34
    // param_1[0x3a] = uVar1;        // +0xe8
    // param_1[0x3b] = uVar1;        // +0xec
    // param_1[0x14] = uVar3;        // +0x50
    // param_1[0x15] = uVar3;        // +0x54
    // param_1[0x16] = uVar6;        // +0x58
    // param_1[0x17] = uVar6;        // +0x5c
    // param_1[0x1a] = uVar6;        // +0x68
    // param_1[0x1b] = uVar6;        // +0x6c
    // param_1[0x1d] = uVar3;        // +0x74
    // param_1[0x23] = uVar2;        // +0x8c
    // param_1[0x25] = uVar5;        // +0x94
    // param_1[0x2d] = uVar4;        // +0xb4
    // param_1[0x2e] = uVar4;        // +0xb8
    // param_1[0x33] = uVar2;        // +0xcc
    // param_1[0x3c] = uVar9;        // +0xf0
    // param_1[0x1c] = uVar7;        // +0x70
    // param_1[0x21] = uVar6;        // +0x84
    // param_1[0x27] = uVar3;        // +0x9c
    // param_1[0x30] = uVar1;        // +0xc0
    // param_1[0x34] = uVar5;        // +0xd0
    // param_1[0x3d] = uVar9;        // +0xf4
    // param_1[0x1e] = uVar7;        // +0x78
    // param_1[0x22] = uVar2;        // +0x88
    // param_1[0x28] = uVar10;       // +0xa0
    // param_1[0x31] = uVar4;        // +0xc4
    // param_1[0x35] = uVar6;        // +0xd4
    // param_1[0x47] = uVar5;        // +0x11c
    // *(undefined1 *)(param_1 + 0xc) = 1; // byte at +0x30
    // param_1[0x12] = uVar8;        // +0x48
    // param_1[0x13] = uVar8;        // +0x4c
    // param_1[0x1f] = uVar1;        // +0x7c
    // param_1[0x20] = uVar1;        // +0x80
    // param_1[0x24] = uVar3;        // +0x90
    // param_1[0x26] = uVar3;        // +0x98
    // param_1[0x29] = uVar2;        // +0xa4
    // param_1[0x2a] = uVar1;        // +0xa8
    // param_1[0x2b] = uVar2;        // +0xac
    // param_1[0x2c] = uVar2;        // +0xb0
    // param_1[0x2f] = uVar2;        // +0xbc
    // param_1[0x32] = uVar4;        // +0xc8
    // param_1[0x36] = uVar6;        // +0xd8
    // param_1[0x37] = 0;            // +0xdc
    // param_1[0x38] = uVar1;        // +0xe0
    // param_1[0x3f] = DAT_00d5ef70; // +0xfc
    // param_1[0x40] = DAT_00d5ddec; // +0x100
    // param_1[0x44] = uVar8;        // +0x110
    // param_1[0x41] = uVar5;        // +0x104
    // param_1[0x45] = uVar4;        // +0x114
    // param_1[0x42] = uVar5;        // +0x108
    // param_1[0x46] = uVar4;        // +0x118
    // param_1[0x3e] = 0;            // +0xf8
    // param_1[0x43] = uVar5;        // +0x10c
    // *param_1 = uVar1;             // +0x00
    // param_1[1] = uVar4;           // +0x04
    // param_1[2] = uVar1;           // +0x08
    // param_1[3] = uVar4;           // +0x0c
    // param_1[5] = uVar3;           // +0x14
    // param_1[8] = uVar3;           // +0x20
    // param_1[9] = uVar3;           // +0x24
    // param_1[0x4a] = 0;            // +0x128
    // param_1[0x4b] = 0;            // +0x12c
    // param_1[0x4c] = 0;            // +0x130
    // param_1[0x4d] = uVar2;        // +0x134
    // param_1[0x51] = 0;            // +0x144

    // We'll use meaningful field names based on typical game config structure.
    // Since we don't know the exact struct, we'll use generic names with offsets.

    // Byte at +0x30 set to 1 (likely a boolean flag)
    thisConfig->byteFlag30 = 1;

    // Initialize all fields from global defaults
    thisConfig->field00 = DAT_00d5780c;
    thisConfig->field04 = DAT_00e445ac;
    thisConfig->field08 = DAT_00d5780c;
    thisConfig->field0C = DAT_00e445ac;
    thisConfig->field14 = DAT_00d5c458;
    thisConfig->field20 = DAT_00d5c458;
    thisConfig->field24 = DAT_00d5c458;
    thisConfig->field34 = DAT_00d5779c;
    thisConfig->field38 = DAT_00d5f6c4;
    thisConfig->field3C = DAT_00d5fb68;
    thisConfig->field40 = DAT_00d5fb68; // uVar6
    thisConfig->field44 = DAT_00d6ef5c;
    thisConfig->field48 = DAT_00d6ef60; // uVar8
    thisConfig->field4C = DAT_00d6ef60;
    thisConfig->field50 = DAT_00d5d7b8; // uVar3
    thisConfig->field54 = DAT_00d5d7b8;
    thisConfig->field58 = DAT_00d6ef58; // uVar6
    thisConfig->field5C = DAT_00d6ef58;
    thisConfig->field60 = DAT_00d5efbc; // uVar5
    thisConfig->field64 = DAT_00d5efbc;
    thisConfig->field68 = DAT_00d6ef58;
    thisConfig->field6C = DAT_00d6ef58;
    thisConfig->field70 = DAT_00d6ef50; // uVar7
    thisConfig->field74 = DAT_00d5d7b8;
    thisConfig->field78 = DAT_00d6ef50;
    thisConfig->field7C = DAT_00d5780c; // uVar1
    thisConfig->field80 = DAT_00d5780c;
    thisConfig->field84 = DAT_00d6ef58; // uVar6
    thisConfig->field88 = DAT_00d5c454; // uVar2
    thisConfig->field8C = DAT_00d5c454; // uVar2
    thisConfig->field90 = DAT_00d5c458; // uVar3
    thisConfig->field94 = DAT_00d5ef8c; // uVar5
    thisConfig->field98 = DAT_00d5c458; // uVar3
    thisConfig->field9C = DAT_00d5ef84; // uVar3
    thisConfig->fieldA0 = DAT_00e44720; // uVar10
    thisConfig->fieldA4 = DAT_00d58cbc; // uVar2
    thisConfig->fieldA8 = DAT_00d5780c; // uVar1
    thisConfig->fieldAC = DAT_00d58cbc; // uVar2
    thisConfig->fieldB0 = DAT_00d58cbc; // uVar2
    thisConfig->fieldB4 = DAT_00d5ef7c; // uVar4
    thisConfig->fieldB8 = DAT_00d5ef7c;
    thisConfig->fieldBC = DAT_00d58cbc; // uVar2
    thisConfig->fieldC0 = DAT_00d5842c; // uVar1
    thisConfig->fieldC4 = DAT_00d5efb4; // uVar4
    thisConfig->fieldC8 = DAT_00d5cf70; // uVar4
    thisConfig->fieldCC = DAT_00d5c454; // uVar2
    thisConfig->fieldD0 = DAT_00d6ef54; // uVar5
    thisConfig->fieldD4 = DAT_00d6ef4c; // uVar6
    thisConfig->fieldD8 = DAT_00d5ef80; // uVar6
    thisConfig->fieldDC = 0;
    thisConfig->fieldE0 = DAT_00d5780c; // uVar1
    thisConfig->fieldE8 = DAT_00d5779c; // uVar1
    thisConfig->fieldEC = DAT_00d5779c;
    thisConfig->fieldF0 = DAT_00e446bc; // uVar9
    thisConfig->fieldF4 = DAT_00e446c0; // uVar9
    thisConfig->fieldF8 = 0;
    thisConfig->fieldFC = DAT_00d5ef70;
    thisConfig->field100 = DAT_00d5ddec;
    thisConfig->field104 = DAT_00d6ef48; // uVar5
    thisConfig->field108 = DAT_00e445fc; // uVar5
    thisConfig->field10C = DAT_00d64730; // uVar5
    thisConfig->field110 = DAT_00d6ef60; // uVar8
    thisConfig->field114 = DAT_00d6ef44; // uVar4
    thisConfig->field118 = DAT_00d620ac; // uVar4
    thisConfig->field11C = DAT_00d5d740; // uVar5
    thisConfig->field128 = 0;
    thisConfig->field12C = 0;
    thisConfig->field130 = 0;
    thisConfig->field134 = DAT_00d58cbc; // uVar2
    thisConfig->field144 = 0;
}