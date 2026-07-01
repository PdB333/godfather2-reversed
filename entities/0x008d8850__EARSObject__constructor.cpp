// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor with flag 0x4000
  FUN_0046e6b0(param_2, 0x4000);
  
  // Set vtable pointer
  *this = &PTR_FUN_00d7da48;
  
  // Initialize member function pointers / interface pointers
  // +0x3C (0xF * 4): Some interface or callback
  this[0xf] = &PTR_LAB_00d7da38;
  // +0x48 (0x12 * 4): Another interface
  this[0x12] = &PTR_LAB_00d7da34;
  // +0x50 (0x14 * 4): Another interface
  this[0x14] = &PTR_LAB_00d7da30;
  // +0x54 (0x15 * 4): Another interface
  this[0x15] = &PTR_LAB_00d7d9d0;
  // +0x58 (0x16 * 4): Another interface
  this[0x16] = &PTR_LAB_00d7d968;
  
  return this;
}