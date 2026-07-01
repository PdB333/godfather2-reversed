// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
  // Call base class constructor (likely EARS::Framework::Object or similar)
  FUN_008928f0();
  
  // If the low bit of flags is set, call a destructor-like function
  // This pattern is typical for placement new / operator delete handling
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}