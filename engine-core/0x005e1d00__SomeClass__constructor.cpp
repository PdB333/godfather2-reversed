// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte initializeFlag)
{
  SomeClass::baseConstructor(this);
  if ((initializeFlag & 1) != 0) {
    SomeClass::operatorDelete(this);
  }
  return this;
}