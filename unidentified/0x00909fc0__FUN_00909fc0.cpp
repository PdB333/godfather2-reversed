// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor
  FUN_0046c590(param_2);
  
  // Set vtable pointer (likely for a base class or interface)
  this[0x14] = &PTR_LAB_00e32854;  // +0x50: vtable or function pointer table
  *this = &PTR_FUN_00d831f0;       // +0x00: primary vtable
  this[0xf] = &PTR_LAB_00d831e0;   // +0x3C: another vtable/function table
  this[0x12] = &PTR_LAB_00d831dc;  // +0x48: another vtable/function table
  this[0x14] = &PTR_LAB_00d831d8;  // +0x50: another vtable/function table
  
  // Initialize 6 slots with magic values (likely for debug/validation)
  // Pattern: 0x91100911, 0xbeefbeef, 0xeac15a55, 0xbadbadba
  // These appear to be 6 groups of 4 fields each (0x18 to 0x2B)
  // Each group: [0x91100911, 0xbeefbeef, 0xeac15a55, 0xbadbadba]
  // +0x60: slot 0
  this[0x18] = 0x91100911;  // +0x60
  this[0x1c] = 0x91100911;  // +0x70
  this[0x20] = 0x91100911;  // +0x80
  this[0x24] = 0x91100911;  // +0x90
  this[0x28] = 0x91100911;  // +0xA0
  this[0x2c] = 0x91100911;  // +0xB0
  
  this[0x16] = 0xbeefbeef;  // +0x58
  this[0x1a] = 0xbeefbeef;  // +0x68
  this[0x1e] = 0xbeefbeef;  // +0x78
  this[0x22] = 0xbeefbeef;  // +0x88
  this[0x26] = 0xbeefbeef;  // +0x98
  this[0x2a] = 0xbeefbeef;  // +0xA8
  
  this[0x17] = 0xeac15a55;  // +0x5C
  this[0x1b] = 0xeac15a55;  // +0x6C
  this[0x1f] = 0xeac15a55;  // +0x7C
  this[0x23] = 0xeac15a55;  // +0x8C
  this[0x27] = 0xeac15a55;  // +0x9C
  this[0x2b] = 0xeac15a55;  // +0xAC
  
  this[0x15] = 0xbadbadba;  // +0x54
  this[0x19] = 0xbadbadba;  // +0x64
  this[0x1d] = 0xbadbadba;  // +0x74
  this[0x21] = 0xbadbadba;  // +0x84
  this[0x25] = 0xbadbadba;  // +0x94
  this[0x29] = 0xbadbadba;  // +0xA4
  
  // Initialize fields to zero
  this[0x31] = 0;           // +0xC4
  *(undefined2 *)(this + 0x32) = 0;  // +0xC8 (2 bytes)
  *(undefined2 *)((int)this + 0xca) = 0;  // +0xCA (2 bytes)
  this[0x33] = 0;           // +0xCC
  *(undefined2 *)(this + 0x34) = 0;  // +0xD0 (2 bytes)
  *(undefined2 *)((int)this + 0xd2) = 0;  // +0xD2 (2 bytes)
  this[0x2f] = 0;           // +0xBC
  this[0x2e] = 0;           // +0xB8
  this[0x2d] = 0;           // +0xB4
  this[0x30] = 0;           // +0xC0
  
  // Call another initialization function
  FUN_00909f20(this);
  
  return this;
}