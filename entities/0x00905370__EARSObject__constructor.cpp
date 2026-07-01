// FUNC_NAME: EARSObject::constructor
undefined4 * __fastcall EARSObject::constructor(undefined4 *this)
{
  // Call base class constructor (likely EARS::Framework::Object or similar)
  FUN_004c26c0();
  
  // Set vtable pointer to the class's vtable
  *this = &PTR_FUN_00e36220;
  
  // Initialize fields at offsets +0x208, +0x20C, +0x210 to zero
  // These are likely reference count, flags, or state variables
  this[0x82] = 0;  // +0x208
  this[0x83] = 0;  // +0x20C
  this[0x84] = 0;  // +0x210
  
  return this;
}