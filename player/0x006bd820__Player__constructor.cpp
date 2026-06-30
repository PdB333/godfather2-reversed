// FUNC_NAME: Player::constructor
undefined4 * __thiscall Player_constructor(undefined4 *this, undefined4 param_2)
{
  undefined4 uVar1;
  
  // Call base class constructor (likely Sentient or Entity)
  FUN_0046c590(param_2);
  
  uVar1 = _DAT_00d5780c; // Some global value (maybe default state or flag)
  
  // Set vtable pointers - multiple vtable entries suggest multiple inheritance or interface
  this[0x14] = &PTR_LAB_00d5e214; // +0x50: vtable for first interface
  *this = &PTR_FUN_00d5ea9c;      // +0x00: main vtable
  this[0xf] = &PTR_LAB_00d5ea8c;  // +0x3C: vtable for second interface
  this[0x12] = &PTR_LAB_00d5ea88; // +0x48: vtable for third interface
  this[0x14] = &PTR_LAB_00d5ea70; // +0x50: vtable for fourth interface (overwrites previous)
  
  // Initialize player state variables
  this[0x15] = 0;          // +0x54: some state/flag
  this[0x16] = 0;          // +0x58: some state/flag
  this[0x17] = 0xffffffff; // +0x5C: invalid/initial value (-1)
  
  // Initialize position/vector components (4 floats each)
  this[0x1b] = 0;          // +0x6C: vector component 0
  this[0x1a] = 0;          // +0x68: vector component 1
  this[0x19] = 0;          // +0x64: vector component 2
  this[0x18] = 0;          // +0x60: vector component 3
  
  this[0x1c] = 0;          // +0x70: some value
  *(undefined2 *)(this + 0x1d) = 0; // +0x74: short value
  *(undefined2 *)((int)this + 0x76) = 0; // +0x76: short value
  this[0x1e] = 0;          // +0x78: some value
  *(undefined2 *)(this + 0x1f) = 0; // +0x7C: short value
  *(undefined2 *)((int)this + 0x7e) = 0; // +0x7E: short value
  this[0x20] = 0;          // +0x80: some value
  *(undefined2 *)(this + 0x21) = 0; // +0x84: short value
  *(undefined2 *)((int)this + 0x86) = 0; // +0x86: short value
  
  // Initialize health/state arrays (5 entries at offsets +0xD0, +0xCC, +0xC8, +0xC4, +0x90)
  this[0x34] = 0;          // +0xD0: health/state 5
  this[0x33] = uVar1;      // +0xCC: health/state 4
  this[0x2e] = uVar1;      // +0xB8: health/state 3
  this[0x29] = uVar1;      // +0xA4: health/state 2
  this[0x24] = uVar1;      // +0x90: health/state 1
  
  // Initialize more state variables
  this[0x27] = 0;          // +0x9C: some state
  this[0x28] = 0;          // +0xA0: some state
  this[0x26] = 0;          // +0x98: some state
  this[0x25] = 0;          // +0x94: some state
  
  this[0x2b] = 0;          // +0xAC: some state
  this[0x2d] = 0;          // +0xB4: some state
  this[0x2c] = 0;          // +0xB0: some state
  this[0x2a] = 0;          // +0xA8: some state
  
  this[0x2f] = 0;          // +0xBC: some state
  this[0x32] = 0;          // +0xC8: some state
  this[0x31] = 0;          // +0xC4: some state
  this[0x30] = 0;          // +0xC0: some state
  
  // If there's a global data buffer, copy 0x8000 bytes into this+0x3C
  if (DAT_0120e93c != 0) {
    FUN_00408900(this + 0xf, &DAT_0120e93c, 0x8000);
  }
  
  return this;
}