// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x00542920
  EARSObject::baseConstructor();
  
  // If bit 0 of flags is set, call a virtual function through the vtable
  // The vtable pointer is obtained from DAT_01223410 + 0x2d4 (likely a global vtable table)
  if ((flags & 1) != 0) {
    // Call vtable[0x2d4] + 4 (second function in that vtable entry)
    (**(code **)(**(int **)(DAT_01223410 + 0x2d4) + 4))(this, 0);
  }
  
  return this;
}