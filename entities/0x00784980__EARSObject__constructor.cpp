// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject_constructor(undefined4 *this, undefined4 param_2)
{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  // Call base class constructor (likely EARS::Framework::Object or similar)
  FUN_0046c590(param_2);
  
  // Initialize member variables with global constants
  // +0x54 (0x15*4): Some float/vector value
  this[0x15] = DAT_00e446f4;
  // +0x58, +0x5C: More vector/color components
  uVar1 = DAT_00d5efa4;
  this[0x16] = DAT_00d5efa4;
  this[0x17] = uVar1;
  // +0x50, +0x6C: Another set of values
  uVar1 = DAT_00d5d7b8;
  this[0x14] = DAT_00d5d7b8;
  this[0x1b] = uVar1;
  // +0x60, +0x64, +0x70, +0x68: More initialization
  this[0x18] = DAT_00e44620;
  this[0x19] = DAT_00d62bd4;
  this[0x1c] = DAT_00d5d740;
  this[0x1a] = _DAT_00d69734;
  // +0x74: Another value
  this[0x1d] = DAT_00e44658;
  
  // Set vtable pointer and function pointers
  // +0x00: vtable
  *this = &PTR_FUN_00d69718;
  // +0x3C (0xF*4): Some function pointer table
  this[0xf] = &PTR_LAB_00d69708;
  // +0x48 (0x12*4): Another function pointer
  this[0x12] = &PTR_LAB_00d69704;
  
  // +0x88 (0x22*4): Initialize with magic constants (likely sentinel values)
  this[0x22] = 0x358fa2c2;
  this[0x23] = 8;
  this[0x24] = 2;
  this[0x25] = 6;
  
  // +0x78, +0x80, +0x7C, +0x84: More initialization
  this[0x1e] = 0;
  this[0x20] = 0;
  this[0x1f] = DAT_00d5ccf8;
  this[0x21] = 0;
  
  // +0x98-0xA4: Magic constants for object identification/debugging
  this[0x26] = 0xbadbadba;
  this[0x27] = 0xbeefbeef;
  this[0x28] = 0xeac15a55;
  this[0x29] = 0x91100911;
  
  // +0xAC: Another magic constant
  this[0x2b] = 0xbadbadba;
  // +0xC0: Yet another
  this[0x30] = 0xbadbadba;
  // +0xB0-0xBC: More magic constants
  this[0x2c] = 0xbeefbeef;
  this[0x2d] = 0xeac15a55;
  this[0x2e] = 0x91100911;
  // +0xC4-0xCC: More magic
  this[0x31] = 0xbeefbeef;
  this[0x32] = 0xeac15a55;
  this[0x33] = 0x91100911;
  
  // +0xD4-0xE0: More magic constants
  this[0x35] = 0xbadbadba;
  this[0x36] = 0xbeefbeef;
  this[0x37] = 0xeac15a55;
  this[0x38] = 0x91100911;
  
  // +0xE8-0xFC: More magic constants
  this[0x3a] = 0xbadbadba;
  this[0x3f] = 0xbadbadba;
  this[0x3b] = 0xbeefbeef;
  this[0x3c] = 0xeac15a55;
  this[0x3d] = 0x91100911;
  this[0x40] = 0xbeefbeef;
  this[0x41] = 0xeac15a55;
  this[0x42] = 0x91100911;
  
  // +0x110-0x12C: More magic constants
  this[0x44] = 0xbadbadba;
  this[0x45] = 0xbeefbeef;
  this[0x46] = 0xeac15a55;
  this[0x47] = 0x91100911;
  this[0x48] = 0xbadbadba;
  this[0x49] = 0xbeefbeef;
  this[0x4a] = 0xeac15a55;
  this[0x4b] = 0x91100911;
  this[0x4c] = 0xbadbadba;
  this[0x4d] = 0xbeefbeef;
  this[0x4e] = 0xeac15a55;
  this[0x4f] = 0x91100911;
  
  // +0x458 (0x116*4): Set byte to 0
  uVar1 = DAT_00d69700;
  *(undefined1 *)(this + 0x116) = 0;
  
  // Copy data from global table (0xC6 * 4 = 0x318 bytes)
  puVar3 = &DAT_00e52478;
  puVar4 = this + 0x50;
  for (iVar2 = 0xc6; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  
  // Reset some fields to 0 after copying
  this[0x2a] = uVar1;
  this[0x2b] = 0;
  this[0x2e] = 0;
  this[0x2d] = 0;
  this[0x2c] = 0;
  
  // More resetting with different base values
  this[0x39] = uVar1;
  uVar1 = DAT_00d696fc;
  this[0x3a] = 0;
  this[0x3d] = 0;
  this[0x3c] = 0;
  this[0x3b] = 0;
  
  this[0x2f] = uVar1;
  this[0x33] = 0;
  this[0x32] = 0;
  this[0x31] = 0;
  this[0x30] = 0;
  
  this[0x3e] = uVar1;
  uVar1 = DAT_00d5e288;
  this[0x42] = 0;
  this[0x41] = 0;
  this[0x40] = 0;
  this[0x3f] = 0;
  this[0x38] = 0;
  this[0x37] = 0;
  this[0x36] = 0;
  this[0x35] = 0;
  this[0x47] = 0;
  this[0x46] = 0;
  this[0x45] = 0;
  this[0x44] = 0;
  
  this[0x34] = uVar1;
  this[0x43] = uVar1;
  
  // Copy data from global buffers if they exist
  if (DAT_0120e924 != 0) {
    FUN_00408900(this + 0xf, &DAT_0120e924, 0x8000);
  }
  if (DAT_0120e91c != 0) {
    FUN_00408900(this + 0xf, &DAT_0120e91c, 0x8000);
  }
  
  return this;
}