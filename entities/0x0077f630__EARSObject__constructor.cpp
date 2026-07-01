// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
  EARSObject::baseConstructor(); // FUN_0077ef20 - likely initializes base class members
  if ((flags & 1) != 0) {
    EARSObject::operatorDelete(this); // FUN_00624da0 - deallocation if flag indicates heap allocation
  }
  return this;
}