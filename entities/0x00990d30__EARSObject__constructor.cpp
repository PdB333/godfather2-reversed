// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
  // Call base class constructor (likely EARS::Framework::Object or similar)
  EARSObject::baseConstructor(this);
  
  // If the low bit of flags is set, call the destructor registration
  // This pattern is typical for EA's placement new / operator delete handling
  if ((flags & 1) != 0) {
    // Register destructor for proper cleanup (likely operator delete or similar)
    EARSObject::registerDestructor(this);
  }
  
  return this;
}