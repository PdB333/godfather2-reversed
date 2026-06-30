// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
  int *vtable;
  
  EARSObject::baseConstructor();
  if ((flags & 1) != 0) {
    vtable = (int *)EARSObject::getVtable();
    (**(code **)(*vtable + 4))(this, 0x170); // set vtable at offset 0x170
  }
  return this;
}