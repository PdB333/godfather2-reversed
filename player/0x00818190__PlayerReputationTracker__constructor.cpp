// FUNC_NAME: PlayerReputationTracker::constructor
undefined4 * __thiscall PlayerReputationTracker__constructor(undefined4 *this,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  FUN_0046c590(param_2);
  uVar2 = DAT_00d5e288;
  uVar1 = _DAT_00d5780c;
  this[0x15] = _DAT_00d5780c;  // +0x54 - reputation value
  this[0x18] = uVar1;          // +0x60 - some threshold
  uVar1 = DAT_00d5ccf8;
  this[0x1b] = uVar2;          // +0x6C - another reputation value
  this[0x1c] = uVar1;          // +0x70 - related value
  this[0x1e] = uVar2;          // +0x78 - duplicate
  uVar2 = _DAT_00d5cf70;
  this[0x20] = uVar1;          // +0x80
  this[0x21] = uVar1;          // +0x84
  uVar1 = DAT_00d58cbc;
  *this = &PTR_FUN_00d73204;   // +0x00 - vtable pointer
  this[0xf] = &PTR_LAB_00d731f4;  // +0x3C
  this[0x12] = &PTR_LAB_00d731f0; // +0x48
  this[0x14] = 0;              // +0x50 - initialized to 0
  this[0x16] = 0;              // +0x58
  this[0x17] = 0;              // +0x5C
  this[0x19] = 0;              // +0x64
  this[0x1a] = 500;            // +0x68 - some max value (500)
  *(undefined1 *)(this + 0x1d) = 0;  // +0x74 - byte flag
  *(undefined1 *)(this + 0x1f) = 1;  // +0x7C - byte flag
  this[0x22] = uVar1;          // +0x88
  this[0x23] = uVar2;          // +0x8C
  this[0x24] = 0;              // +0x90
  this[0x25] = 0;              // +0x94
  this[0x26] = 0;              // +0x98
  this[0x27] = 0;              // +0x9C
  this[0x28] = uVar1;          // +0xA0
  this[0x29] = uVar2;          // +0xA4
  this[0x2a] = 0;              // +0xA8
  this[0x2b] = 0;              // +0xAC
  this[0x2c] = 0;              // +0xB0
  this[0x2d] = 0;              // +0xB4
  this[0x2e] = 0;              // +0xB8
  this[0x2f] = 2000;           // +0xBC - another threshold (2000)
  this[0x30] = 0;              // +0xC0
  this[0x31] = 0;              // +0xC4
  this[0x32] = uVar1;          // +0xC8
  this[0x33] = uVar2;          // +0xCC
  this[0x34] = 0;              // +0xD0
  this[0x71] = 0;              // +0x1C4
  this[0x72] = 0;              // +0x1C8
  this[0x73] = 0;              // +0x1CC
  this[0x74] = 0;              // +0x1D0
  this[0x75] = 0;              // +0x1D4
  this[0x76] = 0;              // +0x1D8
  this[0x77] = 0;              // +0x1DC
  return this;
}