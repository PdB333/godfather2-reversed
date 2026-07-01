// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
  // Call base class constructor
  FUN_00938710();
  
  // If the 'delete on release' flag is set, register for deletion
  if ((flags & 1) != 0) {
    FUN_005c4480(this); // likely registerForDeletion or similar
  }
  
  return this;
}