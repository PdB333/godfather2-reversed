// FUNC_NAME: GameConfig::initializeDefaults

void __fastcall GameConfig::initializeDefaults(int* config) {
    // Load default values from global config constants
    // Offsets are in 4-byte units unless noted

    // Zero out many fields
    config[10] = 0;       // +0x28
    config[0xb] = 0;      // +0x2c

    // Set fields from global constants
    int uVar10 = DAT_00e445ac;  // some global
    int uVar4  = DAT_00d5efbc;
    int uVar9  = DAT_00d5efb8;
    int uVar8  = DAT_00d5efb4;
    int uVar6  = DAT_00d5eee4;
    int uVar2  = _DAT_00d5ca64;
    int uVar3  = DAT_00d5842c;
    int uVar1  = DAT_00d5779c;

    config[0xf]  = uVar2;  // +0x3c
    config[0x10] = uVar2;  // +0x40
    config[0x11] = DAT_00d5efb0;  // +0x44
    config[0x12] = DAT_00d5efac;  // +0x48
    config[0x14] = DAT_00d5efa8;  // +0x50
    config[0x15] = DAT_00e44620;  // +0x54
    config[0x16] = DAT_00d5efa4;  // +0x58
    int uVar2_prev = DAT_00d5efa0;
    config[0x17] = uVar2_prev;   // +0x5c
    config[0x1a] = uVar2_prev;   // +0x68
    config[0x1b] = uVar2_prev;   // +0x6c
    int uVar2_new = DAT_00d5ef9c;
    config[0x1f] = uVar4;        // +0x7c
    int uVar4_new = DAT_00d5ef98;
    config[0x1c] = uVar2_new;    // +0x70
    int uVar2_again = DAT_00d5d7b8;
    config[0x20] = uVar4_new;    // +0x80
    int uVar4_again = DAT_00d5ef94;
    config[0x1d] = uVar2_again;  // +0x74
    config[0x2d] = uVar2_again;  // +0xb4
    config[0x2e] = uVar2_again;  // +0xb8
    int uVar2_2 = DAT_00d5833c;
    config[0x21] = uVar4_again;  // +0x84
    int uVar4_2 = DAT_00d5ef90;
    int uVar5 = DAT_00d5ef98;
    config[0x30] = uVar2_2;      // +0xc0
    config[0x22] = uVar4_2;      // +0x88
    int uVar2_3 = DAT_00d5ef8c;
    config[0x32] = uVar5;        // +0xc8
    int uVar4_3 = DAT_00d5ef88;
    config[0x25] = uVar2_3;      // +0x94
    int uVar2_4 = DAT_00d5ef84;
    config[0x33] = uVar4_3;      // +0xcc
    int uVar4_4 = DAT_00e44630;
    config[0x27] = uVar2_4;      // +0x9c
    int uVar2_5 = DAT_00e44720;
    int uVar7 = DAT_00d5ef80;
    config[0x35] = uVar4_4;      // +0xd4
    config[0x18] = uVar9;        // +0x60
    config[0x19] = uVar8;        // +0x64
    int uVar5_2 = _DAT_00d5c458;
    config[0x24] = uVar3;        // +0x90
    config[0x28] = uVar2_5;      // +0xa0
    int uVar4_5 = DAT_00d58cbc;
    config[0x2a] = uVar3;        // +0xa8
    int uVar3_2 = DAT_00d5c454;
    config[0x34] = uVar9;        // +0xd0
    int uVar2_6 = _DAT_00d5780c;
    config[0x36] = uVar7;        // +0xd8

    // Byte field at offset +0x30
    *(unsigned char*)(config + 0xc) = 1;   // +0x30  (interpreted as byte)

    config[0xd] = uVar6;        // +0x34
    config[0xe] = uVar1;        // +0x38
    config[0x13] = uVar10;      // +0x4c
    config[0x1e] = uVar5_2;     // +0x78
    config[0x23] = uVar5_2;     // +0x8c
    config[0x26] = uVar5_2;     // +0x98
    config[0x29] = uVar4_5;     // +0xa4
    config[0x2b] = uVar3_2;     // +0xac
    config[0x2c] = uVar3_2;     // +0xb0
    config[0x2f] = uVar4_5;     // +0xbc
    config[0x31] = uVar4_5;     // +0xc4

    config[0x37] = 0;           // +0xdc
    config[0x38] = uVar2_6;     // +0xe0
    config[0x3a] = DAT_00d5ef7c; // +0xe8
    config[0x3c] = DAT_00d5ef78; // +0xf0
    config[0x3d] = DAT_00d5ef74; // +0xf4

    int uVar3_3 = DAT_00d5d740;
    config[0x4d] = uVar4_5;     // +0x134
    int uVar4_6 = DAT_00d5ef70;
    config[0x47] = uVar3_3;     // +0x11c
    int uVar7_2 = DAT_00e44618;
    config[0] = uVar4_6;        // +0x00
    int uVar3_4 = DAT_00d5ef6c;
    config[0x48] = uVar7_2;     // +0x120
    int uVar4_7 = DAT_00d5ef50;
    config[2] = uVar3_4;        // +0x08
    int uVar3_5 = DAT_00d5eee0;
    config[0x39] = 0;           // +0xe4
    config[0x3b] = uVar1;       // +0xec
    config[0x3e] = 0;           // +0xf8
    config[0x49] = uVar4_7;     // +0x124
    config[0x4a] = 0;           // +0x128
    config[0x4b] = 0;           // +0x12c
    config[0x4c] = 0;           // +0x130
    config[0x46] = 0;           // +0x118
    config[0x45] = 0;           // +0x114
    config[0x44] = 0;           // +0x110
    config[0x43] = 0;           // +0x10c
    config[0x42] = 0;           // +0x108
    config[0x41] = 0;           // +0x104
    config[0x40] = 0;           // +0x100
    config[0x3f] = 0;           // +0xfc

    config[1] = uVar10;         // +0x04
    config[3] = uVar6;          // +0x0c
    config[4] = uVar2_6;        // +0x10
    config[5] = uVar5_2;        // +0x14
    config[6] = uVar1;          // +0x18
    config[7] = uVar3_5;        // +0x1c
    config[8] = uVar5_2;        // +0x20
    config[9] = uVar5_2;        // +0x24

    config[0x50] = 0;           // +0x140
    config[0x4f] = 0;           // +0x13c
    config[0x4e] = 0;           // +0x138
    config[0x51] = 0;           // +0x144
}