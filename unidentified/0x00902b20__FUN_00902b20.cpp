// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor at 0x00901860
  FUN_00901860(param_2);
  
  // Set vtable pointer
  *this = &PTR_FUN_00d81db0;
  
  // Initialize various member pointers at specific offsets
  // +0x3C (0xF * 4)
  this[0xf] = &PTR_LAB_00d81da0;
  // +0x48 (0x12 * 4)
  this[0x12] = &PTR_LAB_00d81d9c;
  // +0x50 (0x14 * 4)
  this[0x14] = &PTR_LAB_00d81d98;
  // +0x54 (0x15 * 4)
  this[0x15] = &PTR_LAB_00d81d38;
  // +0x58 (0x16 * 4)
  this[0x16] = &PTR_LAB_00d81cd0;
  
  // Call some initialization function with parameter 0
  FUN_004c14e0(0);
  
  return this;
}