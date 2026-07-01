// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 param_2)
{
  // Set vtable pointer
  *this = &PTR_LAB_00d74e54;
  
  // Store parameter
  this[1] = param_2;
  
  // Call some initialization function three times (likely for different subsystems)
  FUN_004a8ec0(0);
  FUN_004a8ec0(0);
  FUN_004a8ec0(0);
  
  // Initialize various fields to 0
  this[0xf] = 0;  // +0x3C
  this[0x10] = 0; // +0x40
  this[0x11] = 0; // +0x44
  this[0x12] = 0; // +0x48
  this[0x13] = 0; // +0x4C
  this[0xe] = 0;  // +0x38
  this[0x14] = 1; // +0x50 - Set to 1 (maybe a flag or count)
  
  // More field initializations to 0
  this[10] = 0;   // +0x28
  this[9] = 0;    // +0x24
  this[8] = 0;    // +0x20
  this[0xd] = 0;  // +0x34
  this[0xc] = 0;  // +0x30
  this[0xb] = 0;  // +0x2C
  
  return this;
}