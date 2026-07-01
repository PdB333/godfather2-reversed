// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
  // Call base class constructor (likely EARS::Framework::Object or similar)
  FUN_0097f0a0();
  
  // If the low bit of flags is set, call the destructor (for placement new cleanup?)
  if ((flags & 1) != 0) {
    FUN_005c4480(this);
  }
  
  return this;
}