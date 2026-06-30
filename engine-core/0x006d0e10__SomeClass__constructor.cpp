// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  int *vtablePtr;
  
  BaseClass::constructor();
  if ((flags & 1) != 0) {
    vtablePtr = (int *)getVtable();
    (**(code **)(*vtablePtr + 4))(this, 0x60); // call operator delete at vtable+4 with size 0x60
  }
  return this;
}