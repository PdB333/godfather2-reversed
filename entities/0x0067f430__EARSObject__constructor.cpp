// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
  int *vtable;
  
  EARSObject::baseConstructor();
  if ((flags & 1) != 0) {
    vtable = (int *)EARSObject::getVtable();
    (**(code **)(*vtable + 4))(this,0x70);
  }
  return this;
}