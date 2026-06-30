// FUNC_NAME: PlayerSettings::PlayerSettings
undefined4 * __thiscall PlayerSettings::PlayerSettings(undefined4 *this, undefined4 parentObj)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;

  // Call base class constructor with parent object
  baseClassConstructor(parentObj);

  // Cache global defaults
  uVar5 = g_defaultSomeValue1;  // DAT_00d5eee4
  uVar2 = g_defaultSomeValue2;  // DAT_00d5c454
  uVar4 = g_defaultZero;        // _DAT_00d5780c (likely 0 or a sentinel)
  uVar1 = g_defaultSomeValue3;  // DAT_00d5779c

  // Initialize vtable and sub-vtable pointers
  this[0x43] = g_defaultSomeValue2;  // +0x10C
  this[0x44] = uVar2;                // +0x110
  *this = &VTABLE_Ptr_00d62090;      // +0x000 main vtable
  this[0xf] = &VTABLE_Sub_00d62080;  // +0x03C sub vtable A
  this[0x12] = &VTABLE_Sub_00d6207c; // +0x048 sub vtable B

  // Settings values (likely AI/behavior parameters)
  this[0x45] = 5;      // +0x114 number of something
  this[0x46] = 2000;   // +0x118 max range / health?
  this[0x47] = 3;      // +0x11C
  this[0x48] = 2;      // +0x120
  this[0x49] = uVar4;  // +0x124 zero
  this[0x4a] = 0;      // +0x128
  this[0x4b] = uVar4;  // +0x12C
  this[0x4c] = uVar4;  // +0x130
  this[0x4d] = 0;      // +0x134
  this[0x4e] = uVar4;  // +0x138
  this[0x4f] = uVar4;  // +0x13C
  this[0x50] = uVar4;  // +0x140
  this[0x51] = uVar5;  // +0x144
  this[0x52] = uVar1;  // +0x148
  this[0x53] = 0;      // +0x14C
  this[0x54] = 0;      // +0x150
  this[0x58] = 0;      // +0x160
  this[0x57] = 0;      // +0x15C
  this[0x56] = 0;      // +0x158
  this[0x55] = 0;      // +0x154
  this[0x59] = 0;      // +0x164
  this[0x5a] = 0;      // +0x168
  this[0x5e] = 0;      // +0x178
  this[0x5d] = 0;      // +0x174
  this[0x5c] = 0;      // +0x170
  this[0x5b] = 0;      // +0x16C
  this[0x5f] = 0;      // +0x17C
  this[0x60] = 0;      // +0x180
  this[100] = 0;       // +0x194 (note: index 100 = +0x190)
  this[99] = 0;        // +0x18C
  this[0x62] = 0;      // +0x188
  this[0x61] = 0;      // +0x184

  // Load blob if a global data pointer is set
  if (g_someDataBlob != 0) {
    loadDataBuffer(this + 0xf, g_someDataBlob, 0x8000); // copy 32KB to +0x3C
    uVar4 = g_defaultZero;        // refresh cached values after copy
    uVar5 = g_defaultSomeValue1;
  }

  // Clear a range of 8-byte fields (likely matrices or vectors)
  *(undefined8 *)(this + 0x14) = 0;  // +0x050
  *(undefined8 *)(this + 0x16) = 0;  // +0x058
  *(undefined8 *)(this + 0x18) = 0;  // +0x060
  *(undefined8 *)(this + 0x1a) = 0;  // +0x068
  *(undefined8 *)(this + 0x1c) = 0;  // +0x070
  *(undefined8 *)(this + 0x1e) = 0;  // +0x078
  *(undefined8 *)(this + 0x20) = 0;  // +0x080

  uVar1 = g_defaultSomeValue4;  // DAT_00d58cbc
  this[0x1d] = g_defaultSomeValue4; // +0x074
  this[0x14] = uVar1;               // +0x050
  this[0x15] = uVar1;               // +0x054
  this[0x1c] = g_defaultSomeValue5; // +0x070 (DAT_00d5ef6c)

  uVar1 = g_defaultSomeValue3;  // DAT_00d5779c
  this[0x25] = 0;      // +0x094
  this[0x30] = 0;      // +0x0C0
  this[0x31] = uVar1;  // +0x0C4

  uVar2 = g_defaultSomeValue6;  // DAT_00d5d7b8
  this[0x2c] = 0;      // +0x0B0
  this[0x37] = 0;      // +0x0DC
  this[0x2d] = 0;      // +0x0B4
  this[0x38] = 0;      // +0x0E0
  this[0x3a] = 0;      // +0x0E8
  this[0x3b] = 0;      // +0x0EC
  this[0x3c] = 0;      // +0x0F0

  uVar1 = g_defaultSomeValue7;  // DAT_00d5842c
  this[0x24] = uVar4;  // +0x090 (uVar4 = zero)
  this[0x2f] = uVar4;  // +0x0BC

  uVar3 = g_defaultSomeValue8;  // DAT_00e446f4
  this[0x27] = uVar2;  // +0x09C
  this[0x2a] = uVar2;  // +0x0A8
  this[0x35] = uVar2;  // +0x0D4

  uVar4 = g_defaultSomeValue9;  // DAT_00d5ddec
  this[0x3d] = uVar1;  // +0x0F4
  uVar2 = g_defaultSomeValue10; // DAT_00d5ef50
  this[0x32] = uVar3;  // +0x0C8
  uVar3 = g_defaultSomeValue11; // DAT_00e445fc
  this[0x2b] = uVar4;  // +0x0AC
  this[0x36] = uVar4;  // +0x0D8
  uVar1 = g_defaultSomeValue12; // _DAT_00d5c458
  this[0x3e] = uVar2;  // +0x0F8
  this[0x3f] = uVar2;  // +0x0FC
  uVar4 = g_defaultSomeValue13; // DAT_00e4475c
  this[0x28] = uVar3;  // +0x0A0
  uVar2 = g_defaultSomeValue14; // DAT_00d620ac
  this[0x2e] = uVar1;  // +0x0B8
  this[0x39] = uVar1;  // +0x0E4
  uVar1 = g_defaultSomeValue15; // _DAT_00d5cf70
  this[0x40] = uVar4;  // +0x100
  uVar4 = g_defaultSomeValue16; // DAT_00d5f520
  this[0x26] = uVar5;  // +0x098
  this[0x33] = uVar2;  // +0x0CC
  this[0x29] = uVar5;  // +0x0A4
  this[0x34] = uVar5;  // +0x0D0
  this[0x42] = uVar1;  // +0x108
  this[0x41] = uVar4;  // +0x104

  return this;
}