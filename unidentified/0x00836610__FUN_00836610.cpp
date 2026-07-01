// FUNC_NAME: SomeClass::constructor
undefined4 * SomeClass::constructor(undefined4 *this, int param2, float param3)
{
  // Call base class constructor or initialization function
  FUN_008334a0();
  
  // Initialize field at offset 0x4C (0x13 * 4) with a global value
  this[0x13] = _DAT_00d5780c;
  
  // Set vtable pointer (offset 0x00)
  *this = &PTR_LAB_00d73738;
  
  // Overwrite field at offset 0x4C with calculated value from param2 + 0x4c * param3
  this[0x13] = *(float *)(param2 + 0x4c) * param3;
  
  return this;
}