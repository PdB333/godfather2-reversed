// FUNC_NAME: PlayerActionableInfo::constructor
undefined4 * __thiscall PlayerActionableInfo::constructor(undefined4 *this, undefined4 param_2)
{
  undefined4 uVar1;
  
  FUN_0046c590(param_2); // Base class constructor (likely Sentient or Entity)
  *this = &PTR_FUN_00d8b4cc; // vtable pointer
  this[0xf] = &PTR_LAB_00d8b4bc; // +0x3C - some function pointer
  this[0x12] = &PTR_LAB_00d8b4b8; // +0x48 - some function pointer
  this[0x14] = 0x25; // +0x50 - some count/flag (37)
  this[0x15] = 0; // +0x54
  this[0x16] = 0xbadbadba; // +0x58 - magic/sentinel value
  this[0x17] = 0xbeefbeef; // +0x5C - magic/sentinel value
  this[0x18] = 0xeac15a55; // +0x60 - magic/sentinel value
  this[0x19] = 0x91100911; // +0x64 - magic/sentinel value
  uVar1 = DAT_00d5ccf8; // Some global value
  this[0x2c] = 0; // +0xB0
  this[0x2d] = 0; // +0xB4
  this[0x2e] = 0; // +0xB8
  this[0x2f] = 0; // +0xBC
  this[0x3d] = uVar1; // +0xF4
  this[0x3e] = uVar1; // +0xF8
  this[0x38] = 0; // +0xE0
  this[0x39] = 0; // +0xE4
  this[0x3a] = 0; // +0xE8
  this[0x3b] = 0; // +0xEC
  this[0x3c] = 0; // +0xF0
  this[0x30] = 2; // +0xC0 - some type/count (2)
  this[0x3f] = 5; // +0xFC - some count (5)
  this[0x40] = 0; // +0x100
  this[0x41] = 0; // +0x104
  this[0x42] = 0; // +0x108
  this[0x43] = 0; // +0x10C
  this[0x44] = 0; // +0x110
  this[0x45] = 0; // +0x114
  this[0x46] = 0; // +0x118
  uVar1 = _DAT_00d5780c; // Some global value
  this[0x47] = 0; // +0x11C
  this[0x48] = 0; // +0x120
  *(undefined2 *)(this + 0x49) = 0; // +0x124 (2 bytes)
  *(undefined2 *)((int)this + 0x126) = 0; // +0x126 (2 bytes)
  this[0x4a] = 0; // +0x128
  *(undefined2 *)(this + 0x4b) = 0; // +0x12C (2 bytes)
  *(undefined2 *)((int)this + 0x12e) = 0; // +0x12E (2 bytes)
  this[0x4c] = 0; // +0x130
  *(undefined2 *)(this + 0x4d) = 0; // +0x134 (2 bytes)
  *(undefined2 *)((int)this + 0x136) = 0; // +0x136 (2 bytes)
  this[0x4e] = 0; // +0x138
  *(undefined2 *)(this + 0x4f) = 0; // +0x13C (2 bytes)
  *(undefined2 *)((int)this + 0x13e) = 0; // +0x13E (2 bytes)
  this[0x50] = 0; // +0x140
  *(undefined2 *)(this + 0x51) = 0; // +0x144 (2 bytes)
  *(undefined2 *)((int)this + 0x146) = 0; // +0x146 (2 bytes)
  this[0x52] = 0; // +0x148
  this[0x54] = 0; // +0x150
  this[0x1c] = uVar1; // +0x70
  this[0x1d] = 0; // +0x74
  this[0x1e] = 0; // +0x78
  this[0x1f] = 0; // +0x7C
  this[0x20] = 0; // +0x80
  this[0x21] = uVar1; // +0x84
  this[0x22] = 0; // +0x88
  this[0x23] = 0; // +0x8C
  this[0x24] = 0; // +0x90
  this[0x25] = 0; // +0x94
  this[0x26] = uVar1; // +0x98
  this[0x27] = 0; // +0x9C
  this[0x28] = 0; // +0xA0
  this[0x29] = 0; // +0xA4
  this[0x2a] = 0; // +0xA8
  this[0x2b] = uVar1; // +0xAC
  this[0x37] = 0; // +0xDC
  this[0x36] = 0; // +0xD8
  this[0x35] = 0; // +0xD4
  this[0x34] = 0; // +0xD0
  return this;
}