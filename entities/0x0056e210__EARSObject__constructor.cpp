// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
  // Call base class constructor or initialization function
  FUN_0056e230();
  
  // If the low bit of flags is set, call the destructor/cleanup function
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}