// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
  // Call base class constructor (likely EARS::Framework::Object or similar)
  EARSObject::baseConstructor();
  
  // If the flags indicate this is a dynamically allocated object (bit 0 set),
  // call the destructor registration function (likely for memory management)
  if ((flags & 1) != 0) {
    EARSObject::registerDestructor(this);
  }
  
  return this;
}