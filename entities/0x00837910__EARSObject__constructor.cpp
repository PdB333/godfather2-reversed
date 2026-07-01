// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
  // Call base class constructor (likely EARS::Framework::Object or similar)
  FUN_00836eb0();
  
  // If the low bit of flags is set, allocate memory for the object
  // +0xE0 is likely a pointer to a vtable or a memory allocation offset
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 0xe0); // Allocate 0xE0 bytes for the object
  }
  
  return this;
}