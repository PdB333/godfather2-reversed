// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x00544450
  EARSObject::baseConstructor();
  
  // If bit 0 of flags is set, call the virtual destructor via vtable
  // The vtable pointer is at offset +0x2d4 from the global DAT_01223410
  if ((flags & 1) != 0) {
    // Call vtable[1] (destructor) with this and 0 (delete flag)
    (**(code **)(**(int **)(DAT_01223410 + 0x2d4) + 4))(this, 0);
  }
  
  return this;
}