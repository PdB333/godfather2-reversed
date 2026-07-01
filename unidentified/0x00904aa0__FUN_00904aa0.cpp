// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor at 0x00477db0
  FUN_00477db0(param_2);
  
  // Set vtable pointer to PTR_FUN_00d82274
  *this = &PTR_FUN_00d82274;
  
  // Initialize member at offset +0x3C (0xF * 4) to PTR_LAB_00d82264
  this[0xf] = &PTR_LAB_00d82264;
  
  // Initialize member at offset +0x48 (0x12 * 4) to PTR_LAB_00d82260
  this[0x12] = &PTR_LAB_00d82260;
  
  // Call some initialization function with global data at 0x01218060
  FUN_00408680(&DAT_01218060);
  
  return this;
}