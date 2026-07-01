// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x008d4230
  EARSObject::baseConstructor();
  
  // If the low bit of flags is set, call the destructor at 0x009c8eb0
  // This is a common pattern for placement new with cleanup on failure
  if ((flags & 1) != 0) {
    EARSObject::destructor(this);
  }
  
  return this;
}