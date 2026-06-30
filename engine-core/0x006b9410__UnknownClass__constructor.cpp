// FUNC_NAME: UnknownClass::constructor
undefined4 * __thiscall UnknownClass::constructor(undefined4 *this,undefined4 param_2)

{
  // Call base class constructor at 0x0046c590
  FUN_0046c590(param_2);
  
  // Initialize member variables
  this[0x14] = 0;                          // +0x50: some pointer/flag
  *this = &PTR_FUN_00d5e618;                // +0x00: vtable pointer
  this[0xf] = &PTR_LAB_00d5e608;            // +0x3C: some function pointer
  this[0x12] = &PTR_LAB_00d5e604;           // +0x48: some function pointer
  this[0x15] = 0xbadbadba;                  // +0x54: magic constant
  this[0x16] = 0xbeefbeef;                  // +0x58: magic constant
  this[0x17] = 0xeac15a55;                  // +0x5C: magic constant
  this[0x18] = 0x91100911;                  // +0x60: magic constant
  this[0x19] = 0;                           // +0x64: some value
  *(undefined2 *)(this + 0x1a) = 0;         // +0x68: 16-bit value
  *(undefined2 *)((int)this + 0x6a) = 0;    // +0x6A: 16-bit value
  this[0x1b] = 0;                           // +0x6C: some pointer/value
  this[0x1c] = 0;                           // +0x70: some pointer/value
  return this;
}