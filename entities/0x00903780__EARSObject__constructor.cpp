// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor at 0x0046c590
  FUN_0046c590(param_2);
  
  // Set vtable pointer (class-specific vtable at 0x00d81f80)
  *this = &PTR_FUN_00d81f80;
  
  // Initialize member fields
  this[0xf] = &PTR_LAB_00d81f70;  // +0x3C - some pointer/interface
  this[0x12] = &PTR_LAB_00d81f6c; // +0x48 - another pointer/interface
  
  // Zero out various fields
  this[0x14] = 0;                 // +0x50 - int/pointer
  *(undefined2 *)(this + 0x15) = 0;  // +0x54 - short (2 bytes)
  *(undefined2 *)((int)this + 0x56) = 0; // +0x56 - short (2 bytes)
  this[0x16] = 0;                 // +0x58 - int/pointer
  *(undefined2 *)(this + 0x17) = 0;  // +0x5C - short (2 bytes)
  *(undefined2 *)((int)this + 0x5E) = 0; // +0x5E - short (2 bytes)
  this[0x18] = 0;                 // +0x60 - int/pointer
  
  return this;
}