// FUNC_NAME: GameConstants::init

void __fastcall GameConstants::init(GameConstants* this)
{
    // WARNING: Globals starting with '_' overlap smaller symbols at the same address

    // Load various global constants into temporary variables
    int uVar10 = g_constant_0x00e445ac;   // some constant
    int uVar4  = g_constant_0x00d5efbc;
    int uVar9  = g_constant_0x00d5efb8;
    int uVar8  = g_constant_0x00d5efb4;
    int uVar6  = g_constant_0x00d5eee4;
    int uVar2  = g_constant_0x00d5ca64;   // note: _DAT_00d5ca64 overlaps
    int uVar3  = g_constant_0x00d5842c;
    int uVar1  = g_constant_0x00d5779c;

    // Zero some fields
    this->field_0x28 = 0;   // offset 0x28 = 10*4
    this->field_0x2c = 0;   // offset 0x2c = 11*4

    // Set fields from constants
    this->field_0x3c = uVar2;  // offset 0x3c = 15*4
    this->field_0x40 = uVar2;  // offset 0x40 = 16*4
    this->field_0x44 = g_constant_0x00d5efb0;
    this->field_0x48 = g_constant_0x00d5efac;
    this->field_0x50 = g_constant_0x00d5efa8;
    this->field_0x54 = g_constant_0x00e44620;
    this->field_0x58 = g_constant_0x00d5efa4;
    uVar2 = g_constant_0x00d5efa0;
    this->field_0x5c = uVar2;   // 0x5c = 23*4
    this->field_0x68 = uVar2;   // 0x68 = 26*4
    this->field_0x6c = uVar2;   // 0x6c = 27*4
    uVar2 = g_constant_0x00d5ef9c;
    this->field_0x7c = uVar4;   // 0x7c = 31*4
    uVar4 = g_constant_0x00d5ef98;
    this->field_0x70 = uVar2;   // 0x70 = 28*4
    uVar2 = g_constant_0x00d5d7b8;
    this->field_0x80 = uVar4;   // 0x80 = 32*4
    uVar4 = g_constant_0x00d5ef94;
    this->field_0x74 = uVar2;   // 0x74 = 29*4
    this->field_0xb4 = uVar2;   // 0xb4 = 45*4
    this->field_0xb8 = uVar2;   // 0xb8 = 46*4
    uVar2 = g_constant_0x00d5833c;
    this->field_0x84 = uVar4;   // 0x84 = 33*4
    uVar4 = g_constant_0x00d5ef90;
    this->field_0xc0 = uVar2;   // 0xc0 = 48*4
    uVar5 = g_constant_0x00d5ef98;
    this->field_0x88 = uVar4;   // 0x88 = 34*4
    uVar2 = g_constant_0x00d5ef8c;
    this->field_0xc8 = uVar5;   // 0xc8 = 50*4
    uVar4 = g_constant_0x00d5ef88;
    this->field_0x94 = uVar2;   // 0x94 = 37*4
    uVar2 = g_constant_0x00d5ef84;
    this->field_0xcc = uVar4;   // 0xcc = 51*4
    uVar4 = g_constant_0x00e44630;
    this->field_0x9c = uVar2;   // 0x9c = 39*4
    uVar2 = g_constant_0x00e44720;
    this->field_0xd4 = uVar4;   // 0xd4 = 53*4
    uVar7 = g_constant_0x00d5ef80;
    this->field_0x60 = uVar9;   // 0x60 = 24*4
    this->field_0x64 = uVar8;   // 0x64 = 25*4
    uVar5 = g_constant_0x00d5c458;   // _DAT
    this->field_0x90 = uVar3;   // 0x90 = 36*4
    this->field_0xa0 = uVar2;   // 0xa0 = 40*4
    uVar4 = g_constant_0x00d58cbc;
    this->field_0xa8 = uVar3;   // 0xa8 = 42*4
    uVar3 = g_constant_0x00d5c454;
    this->field_0xd0 = uVar9;   // 0xd0 = 52*4
    uVar2 = g_constant_0x00d5780c;   // _DAT
    this->field_0xd8 = uVar7;   // 0xd8 = 54*4

    // Byte assignment at offset 0x30 (48) - cast to byte pointer
    *(uint8_t*)((uintptr_t)this + 0x30) = 1;

    this->field_0x34 = uVar6;   // 0x34 = 13*4
    this->field_0x38 = uVar1;   // 0x38 = 14*4
    this->field_0x4c = uVar10;  // 0x4c = 19*4
    this->field_0x78 = uVar5;   // 0x78 = 30*4
    this->field_0x8c = uVar5;   // 0x8c = 35*4
    this->field_0x98 = uVar5;   // 0x98 = 38*4
    this->field_0xa4 = uVar4;   // 0xa4 = 41*4
    this->field_0xac = uVar3;   // 0xac = 43*4
    this->field_0xb0 = uVar3;   // 0xb0 = 44*4
    this->field_0xbc = uVar4;   // 0xbc = 47*4
    this->field_0xc4 = uVar4;   // 0xc4 = 49*4

    this->field_0xdc = 0;       // 0xdc = 55*4
    this->field_0xe0 = uVar2;   // 0xe0 = 56*4

    this->field_0xe8 = g_constant_0x00d5ef7c;  // 0xe8 = 58*4
    this->field_0xf0 = g_constant_0x00d5ef78;  // 0xf0 = 60*4
    this->field_0xf4 = g_constant_0x00d5ef74;  // 0xf4 = 61*4

    uVar3 = g_constant_0x00d5d740;
    this->field_0x134 = uVar4;   // 0x134 = 77*4
    uVar4 = g_constant_0x00d5ef70;
    this->field_0x11c = uVar3;   // 0x11c = 71*4
    uVar7 = g_constant_0x00e44618;
    this->base = uVar4;          // offset 0x0 = first field
    uVar3 = g_constant_0x00d5ef6c;
    this->field_0x120 = uVar7;   // 0x120 = 72*4
    uVar4 = g_constant_0x00d5ef50;
    this->field_0x08 = uVar3;    // 0x08 = 2*4
    uVar3 = g_constant_0x00d5eee0;

    this->field_0xe4 = 0;       // 0xe4 = 57*4
    this->field_0xec = uVar1;   // 0xec = 59*4
    this->field_0xf8 = 0;       // 0xf8 = 62*4
    this->field_0x124 = uVar4;  // 0x124 = 73*4
    this->field_0x128 = 0;      // 0x128 = 74*4
    this->field_0x12c = 0;      // 0x12c = 75*4
    this->field_0x130 = 0;      // 0x130 = 76*4

    // Zero a range of fields (offsets 0xfc to 0x118 inclusive)
    this->field_0x118 = 0;      // 0x118 = 70*4
    this->field_0x114 = 0;      // 0x114 = 69*4
    this->field_0x110 = 0;      // 0x110 = 68*4
    this->field_0x10c = 0;      // 0x10c = 67*4
    this->field_0x108 = 0;      // 0x108 = 66*4
    this->field_0x104 = 0;      // 0x104 = 65*4
    this->field_0x100 = 0;      // 0x100 = 64*4
    this->field_0x0fc = 0;      // 0xfc = 63*4

    // More field assignments in the first part (offsets 0x04 to 0x24)
    this->field_0x04 = uVar10;  // offset 0x04 = 1*4
    this->field_0x0c = uVar6;   // offset 0x0c = 3*4
    this->field_0x10 = uVar2;   // offset 0x10 = 4*4
    this->field_0x14 = uVar5;   // offset 0x14 = 5*4
    this->field_0x18 = uVar1;   // offset 0x18 = 6*4
    this->field_0x1c = uVar3;   // offset 0x1c = 7*4
    this->field_0x20 = uVar5;   // offset 0x20 = 8*4
    this->field_0x24 = uVar5;   // offset 0x24 = 9*4

    // Zero remaining fields at the end
    this->field_0x140 = 0;      // 0x140 = 80*4
    this->field_0x13c = 0;      // 0x13c = 79*4
    this->field_0x138 = 0;      // 0x138 = 78*4
    this->field_0x144 = 0;      // 0x144 = 81*4

    return;
}