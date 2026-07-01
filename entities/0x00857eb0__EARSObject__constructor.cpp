// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, undefined4 param2, undefined4 param3)
{
  // Call base class constructor (likely EARS::Framework::Object or similar)
  FUN_00414970(param2, param3);
  
  // Initialize member variables
  this[3] = 0;  // +0x0C: some pointer or handle, null
  this[4] = 0;  // +0x10: some pointer or handle, null
  
  // Set vtable pointer
  *this = &PTR_FUN_00d752a0;  // +0x00: vtable pointer for this class
  
  // Set some flag/byte at offset +0x14 (5th element, 4 bytes each)
  *(undefined1 *)(this + 5) = 1;  // +0x14: flag/state byte, initialized to 1
  
  return this;
}