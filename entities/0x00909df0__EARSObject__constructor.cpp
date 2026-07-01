// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
  // Call base class constructor (likely EARS::Framework::Object or similar)
  FUN_00909a80();
  
  // If the low bit of flags is set, call a memory/initialization function
  // with size 0xf0 (240 bytes) - likely allocating or zeroing a sub-object
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 0xf0);
  }
  
  return this;
}