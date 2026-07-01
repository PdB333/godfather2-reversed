// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor at 0x0046c590
  FUN_0046c590(param_2);
  
  // Initialize member fields
  this[0x14] = 0;  // +0x50: some pointer/flag
  this[0x15] = 0;  // +0x54: some pointer/flag
  
  // Set vtable pointer
  *this = &PTR_FUN_00d814a4;  // +0x00: vtable
  
  // Set additional function pointers
  this[0xf] = &PTR_LAB_00d81494;   // +0x3C: function pointer
  this[0x12] = &PTR_LAB_00d81490;  // +0x48: function pointer
  
  // Initialize more fields to zero
  this[0x19] = 0;  // +0x64
  this[0x18] = 0;  // +0x60
  this[0x17] = 0;  // +0x5C
  this[0x16] = 0;  // +0x58
  this[0x1a] = 0;  // +0x68
  
  // Zero out 2-byte fields
  *(undefined2 *)(this + 0x1b) = 0;  // +0x6C: short
  *(undefined2 *)((int)this + 0x6e) = 0;  // +0x6E: short
  
  return this;
}