// FUNC_NAME: SomeClass::constructor
undefined4 * __fastcall SomeClass::constructor(undefined4 *this)
{
  // Call base class constructor
  FUN_004814b0();
  
  // Set vtable pointer
  *this = &PTR_FUN_00d7ab88;
  
  // Initialize member variables to 0
  this[4] = 0;  // +0x10 - some pointer or handle
  this[5] = 0;  // +0x14 - some pointer or handle
  this[6] = 0;  // +0x18 - some pointer or handle
  this[7] = 0;  // +0x1C - some pointer or handle
  
  // Call additional initialization
  FUN_00481530();
  
  return this;
}