// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
  // Call base class constructor (likely EARS::Framework::Object or similar)
  EARSObject::baseConstructor(this);
  
  // If the low bit of flags is set, call the destructor registration function
  // This is a common pattern for EA EARS engine objects where the constructor
  // can optionally register the object for destruction tracking
  if ((flags & 1) != 0) {
    EARSObject::registerDestructor(this);
  }
  
  return this;
}