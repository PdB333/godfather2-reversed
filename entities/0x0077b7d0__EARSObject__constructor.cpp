// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
  // Call base class constructor
  EARSObject::baseConstructor();
  
  // If the 'delete on destruction' flag is set, register for deletion
  if ((flags & 1) != 0) {
    EARSObject::registerForDeletion(this);
  }
  
  return this;
}