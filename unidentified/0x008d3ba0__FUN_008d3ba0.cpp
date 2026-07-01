// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 param2, undefined4 param3)
{
  // Call base class constructor
  FUN_008d3980();
  
  // Store param2 at offset +0x48 (0x12 * 4)
  this[0x12] = param2;
  
  // Set vtable pointer at offset +0x0
  *this = &PTR_FUN_00d7d530;
  
  // Store pointer at offset +0x4C (0x13 * 4)
  this[0x13] = &PTR_LAB_00d7d520;
  
  // Store param3 at offset +0x1C (7 * 4)
  this[7] = param3;
  
  return this;
}