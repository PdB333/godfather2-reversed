// FUNC_NAME: EARSObject::constructor
undefined4 * __fastcall EARSObject::constructor(undefined4 *this)
{
  undefined4 uVar1;
  
  uVar1 = _DAT_00d5780c; // Some global default value (likely 0 or -1)
  this[0] = 0;   // +0x00: vtable pointer or first member
  this[1] = 0;   // +0x04
  this[2] = 0;   // +0x08
  this[3] = 0;   // +0x0C
  this[4] = 0;   // +0x10
  this[10] = 0;  // +0x28
  this[9] = 0;   // +0x24
  this[8] = 0;   // +0x20
  this[0xb] = uVar1; // +0x2C: default value
  this[0xe] = 0; // +0x38
  this[0xd] = 0; // +0x34
  this[0xc] = 0; // +0x30
  this[0xf] = uVar1; // +0x3C: default value
  this[0x12] = 0; // +0x48
  this[0x11] = 0; // +0x44
  this[0x10] = 0; // +0x40
  this[0x13] = uVar1; // +0x4C: default value
  this[0x16] = 0; // +0x58
  this[0x15] = 0; // +0x54
  this[0x14] = 0; // +0x50
  this[0x17] = uVar1; // +0x5C: default value
  FUN_007f3bb0(); // Sub-object constructor call
  this[0x49] = 0; // +0x124
  this[0x4a] = 0; // +0x128
  uVar1 = _DAT_00d5780c;
  *(undefined1 *)(this + 0x48) = 0; // +0x120: byte
  *(undefined1 *)((int)this + 0x121) = 0; // +0x121: byte
  this[0x4e] = 0; // +0x138
  this[0x4d] = 0; // +0x134
  this[0x4c] = 0; // +0x130
  this[0x4f] = uVar1; // +0x13C: default value
  *(undefined1 *)((int)this + 0x146) = 0; // +0x146: byte
  *(undefined1 *)(this + 0x51) = 0; // +0x144: byte
  *(undefined1 *)((int)this + 0x145) = 0; // +0x145: byte
  this[0x5a] = 0; // +0x168
  this[0x58] = 0; // +0x160
  this[0x59] = 0; // +0x164
  this[0x50] = 5; // +0x140: default value 5
  this[0x56] = 0; // +0x158
  this[0x55] = 0; // +0x154
  this[0x54] = 0; // +0x150
  this[0x57] = uVar1; // +0x15C: default value
  *(undefined1 *)(this + 0x5c) = 0; // +0x170: byte
  this[0x5f] = 0; // +0x17C
  this[0x5e] = 0; // +0x178
  this[0x5d] = 0; // +0x174
  this[0x62] = 0; // +0x188
  this[0x61] = 0; // +0x184
  this[0x60] = 0; // +0x180
  this[99] = uVar1; // +0x18C: default value
  this[0x66] = 0; // +0x198
  this[0x65] = 0; // +0x194
  this[100] = 0; // +0x190
  this[0x67] = uVar1; // +0x19C: default value
  this[0x6a] = 0; // +0x1A8
  this[0x69] = 0; // +0x1A4
  this[0x68] = 0; // +0x1A0
  this[0x6b] = uVar1; // +0x1AC: default value
  *(byte *)(this + 0x1b7) = *(byte *)(this + 0x1b7) & 0xf0; // +0x1B7: clear low nibble
  this[0x1b0] = 0; // +0x6C0
  this[0x1b1] = 0; // +0x6C4
  this[0x1b6] = 0; // +0x6D8
  this[0x1b2] = 0; // +0x6C8
  this[0x1b3] = 0; // +0x6CC
  this[0x1b4] = uVar1; // +0x6D0: default value
  this[0x1b5] = uVar1; // +0x6D4: default value
  return this;
}