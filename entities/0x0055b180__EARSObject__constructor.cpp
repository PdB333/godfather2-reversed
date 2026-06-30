// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
  // Call base class constructor or initialization function
  FUN_0055b1d0();
  
  // If the low bit of flags is set, call a virtual function through the vtable
  // The vtable is accessed via a global pointer (DAT_01223410) + 0x2d4 offset
  // This appears to be a post-construction initialization step
  if ((flags & 1) != 0) {
    // Call virtual function at vtable index 1 (offset 4 from vtable base)
    // on the object, passing 0 as a parameter
    (**(code **)(**(int **)(DAT_01223410 + 0x2d4) + 4))(this, 0);
  }
  
  return this;
}