// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
  // Call base class constructor (likely EARS::Framework::Object or similar)
  FUN_005f6630();
  
  // If the low bit of flags is set, call the destructor registration function
  // This is a common pattern for placement new / operator delete registration
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);  // likely operator delete or destructor registration
  }
  
  return this;
}