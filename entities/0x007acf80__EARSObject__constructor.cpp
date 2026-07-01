// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
  FUN_007ac980(); // Base class constructor call
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 300); // Allocate memory or initialize with size 300
  }
  return this;
}