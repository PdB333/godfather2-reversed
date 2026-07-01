// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flag)
{
  baseConstructor();  // FUN_0076d2c0 - base class initialization
  if ((flag & 1) != 0) {
    additionalInit(this);  // FUN_00624da0 - secondary initialization
  }
  return this;
}