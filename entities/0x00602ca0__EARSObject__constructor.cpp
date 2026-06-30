// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x00602cc0
  EARSObject::baseConstructor();
  
  // If the low bit of flags is set, call the destructor (placement delete)
  if ((flags & 1) != 0) {
    EARSObject::destructor(this);
  }
  
  return this;
}