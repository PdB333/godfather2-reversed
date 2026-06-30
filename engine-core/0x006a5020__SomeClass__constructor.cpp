// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flags)
{
  BaseClass::constructor(this);
  if ((flags & 1) != 0) {
    initializeSomething(this, 100);
  }
  return this;
}