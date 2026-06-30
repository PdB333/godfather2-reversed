// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor at 0x0046c590
  FUN_0046c590(param_2);
  
  // Set vtable pointer (first field)
  *this = &PTR_FUN_00d5fdbc;
  
  // Initialize various member fields at known offsets
  // +0x3C (0xF * 4)
  this[0xf] = &PTR_LAB_00d5fdac;
  // +0x48 (0x12 * 4)
  this[0x12] = &PTR_LAB_00d5fda8;
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
  
  // +0x68 (0x1A * 4)
  this[0x1a] = 0;
  // +0x6C (0x1B * 4)
  this[0x1b] = 0;
  // +0x70 (0x1C * 4)
  this[0x1c] = 0;
  // +0x74 (0x1D * 4)
  this[0x1d] = 0;
  
  // +0x78 (0x1E * 4) - 1 byte
  *(undefined1 *)(this + 0x1e) = 0;
  
  return this;
}