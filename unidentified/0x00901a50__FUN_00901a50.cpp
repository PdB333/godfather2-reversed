// FUNC_NAME: UnknownClass::constructor
undefined4 * __thiscall UnknownClass::constructor(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor at 0x0046c590
  FUN_0046c590(param_2);
  
  // Set vtable pointer
  *this = &PTR_FUN_00d81bd0;
  
  // Initialize member fields at various offsets
  // +0x3C (0xF * 4)
  this[0xf] = &PTR_LAB_00d81bc0;
  // +0x48 (0x12 * 4)
  this[0x12] = &PTR_LAB_00d81bbc;
  // +0x50 (0x14 * 4)
  this[0x14] = 0;
  // +0x54 (0x15 * 4) - 2 bytes
  *(undefined2 *)(this + 0x15) = 0;
  // +0x56 - 2 bytes
  *(undefined2 *)((int)this + 0x56) = 0;
  // +0x58 (0x16 * 4)
  this[0x16] = 0;
  // +0x5C (0x17 * 4) - 2 bytes
  *(undefined2 *)(this + 0x17) = 0;
  // +0x5E - 2 bytes
  *(undefined2 *)((int)this + 0x5e) = 0;
  // +0x60 (0x18 * 4)
  this[0x18] = 0;
  // +0x64 (0x19 * 4) - 2 bytes
  *(undefined2 *)(this + 0x19) = 0;
  // +0x66 - 2 bytes
  *(undefined2 *)((int)this + 0x66) = 0;
  // +0x68 (0x1a * 4) - Initialize with sentinel values
  this[0x1a] = 0xbadbadba;
  this[0x1b] = 0xbeefbeef;
  this[0x1c] = 0xeac15a55;
  this[0x1d] = 0x91100911;
  // Then clear them all to zero
  this[0x1d] = 0;
  this[0x1c] = 0;
  this[0x1b] = 0;
  this[0x1a] = 0;
  
  return this;
}