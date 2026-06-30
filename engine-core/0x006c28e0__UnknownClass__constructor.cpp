// FUNC_NAME: UnknownClass::constructor
undefined4 * __thiscall UnknownClass::constructor(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor
  FUN_00473840(param_2);
  
  // Set vtable pointer
  *this = &PTR_FUN_00d5ef08;
  
  // Initialize member pointers at various offsets
  this[0xf] = &PTR_LAB_00d5eef8;  // +0x3C
  this[0x12] = &PTR_LAB_00d5eef4; // +0x48
  this[0x14] = &PTR_LAB_00d5eef0; // +0x50
  
  // Zero out four consecutive fields
  this[0x16] = 0;  // +0x58
  this[0x17] = 0;  // +0x5C
  this[0x18] = 0;  // +0x60
  this[0x19] = 0;  // +0x64
  
  // Call another initialization function
  FUN_006c1360();
  
  return this;
}