// FUNC_NAME: PlayerSM::constructor
undefined4 * __thiscall PlayerSM::constructor(PlayerSM *this, undefined4 initializer)
{
  // Call base class constructor (likely EARS object or state machine base)
  FUN_0046c590(initializer);
  
  // Set vtable pointer (index 0)
  *this = &PTR_FUN_00d724cc;
  
  // Initialize vtable-related pointers at offsets 0x3C and 0x48
  this[0xf] = &PTR_LAB_00d724bc; // +0x3C
  this[0x12] = &PTR_LAB_00d724b8; // +0x48
  
  // Zero out shorts at offsets 0x54 and 0x56
  *(undefined2 *)(this + 0x15) = 0; // +0x54
  *(undefined2 *)((int)this + 0x56) = 0; // +0x56
  
  // Initialize sentinel markers for debugging (0xbadbadba, 0xbeefbeef)
  this[0x16] = 0xbadbadba; // +0x58
  this[0x17] = 0xbeefbeef; // +0x5C
  this[0x1a] = 0xbadbadba; // +0x68
  this[0x1b] = 0xbeefbeef; // +0x6C
  
  // Clear byte at offset 0x78
  *(undefined1 *)(this + 0x1e) = 0; // +0x78
  
  // Zero out several integer fields
  this[0x14] = 0; // +0x50
  this[0x19] = 0; // +0x64
  this[0x18] = 0; // +0x60
  this[0x17] = 0; // +0x5C (overwrites sentinel)
  this[0x16] = 0; // +0x58 (overwrites sentinel)
  this[0x1d] = 0; // +0x74
  this[0x1c] = 0; // +0x70
  this[0x1b] = 0; // +0x6C (overwrites sentinel)
  this[0x1a] = 0; // +0x68 (overwrites sentinel)
  
  // Set a default state/type value to 4 at offset 0x7C
  this[0x1f] = 4; // +0x7C
  
  return this;
}