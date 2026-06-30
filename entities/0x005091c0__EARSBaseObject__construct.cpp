// FUNC_NAME: EARSBaseObject::construct
undefined4 __thiscall EARSBaseObject::construct(undefined4 thisObj, byte flags)
{
  int *vtablePtr;

  // Call base class / standard initialization
  initBase();

  // If bit 0 is set, call the virtual function at index 1 (typically allocate or post-construct)
  if ((flags & 1) != 0) {
    vtablePtr = (int *)getVtable();
    (**(code **)(*vtablePtr + 4))(thisObj, 0);
  }

  return thisObj;
}