// FUNC_NAME: SomeClass::constructor
undefined4 * __fastcall SomeClass::constructor(undefined4 *this)
{
  // Store this pointer to global DAT_0112e2ec
  DAT_0112e2ec = this;
  
  // Set vtable pointer at +0x00 to PTR_FUN_00d8baa8
  *this = &PTR_FUN_00d8baa8;
  
  // Set vtable pointer at +0x04 to PTR_LAB_00d8ba98
  this[1] = &PTR_LAB_00d8ba98;
  
  // Set field at +0x08 to 1
  this[2] = 1;
  
  // Set field at +0x0C to 0
  this[3] = 0;
  
  // Call allocation function with size 0x10 (16 bytes)
  FUN_0094f2c0(0x10);
  
  return this;
}