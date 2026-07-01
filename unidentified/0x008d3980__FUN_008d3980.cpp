// FUNC_NAME: SomeClass::constructor
undefined4 * __fastcall SomeClass::constructor(undefined4 *this)
{
  undefined4 uVar1;
  
  // Call base class constructor
  FUN_008d2820();
  
  // Store global value
  uVar1 = _DAT_00d5780c;
  
  // Initialize vtable pointer at +0x4C (0x13 * 4)
  this[0x13] = &PTR_FUN_00e2f19c;
  
  // Set some flag/counter at +0x50 (0x14 * 4)
  this[0x14] = 1;
  
  // Initialize value at +0x54 (0x15 * 4)
  this[0x15] = 0;
  
  // Set primary vtable pointer at +0x00
  *this = &PTR_FUN_00d7d4d8;
  
  // Override vtable entry at +0x4C (0x13 * 4) with another pointer
  this[0x13] = &PTR_LAB_00d7d4c8;
  
  // Initialize value at +0x58 (0x16 * 4)
  this[0x16] = 0;
  
  // Zero out 2-byte fields at +0x5C and +0x5E
  *(undefined2 *)(this + 0x17) = 0;
  *(undefined2 *)((int)this + 0x5e) = 0;
  
  // Initialize value at +0x60 (0x18 * 4)
  this[0x18] = 0;
  
  // Set value at +0x64 (0x19 * 4) to global
  this[0x19] = uVar1;
  
  // Initialize value at +0x68 (0x1A * 4)
  this[0x1a] = 0;
  
  // Zero out 2-byte fields at +0x6C and +0x6E
  *(undefined2 *)(this + 0x1b) = 0;
  *(undefined2 *)((int)this + 0x6e) = 0;
  
  // Initialize value at +0x7C (0x1F * 4)
  this[0x1f] = 0;
  
  // Zero out byte at +0x80 (0x20 * 4)
  *(undefined1 *)(this + 0x20) = 0;
  
  // Initialize values at +0x70 (0x1C * 4), +0x74 (0x1D * 4), +0x78 (0x1E * 4)
  this[0x1c] = 0;
  this[0x1d] = uVar1;
  this[0x1e] = 0;
  
  return this;
}