// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flags)
{
  SomeClass::baseConstructor(this);
  if ((flags & 1) != 0) {
    SomeClass::destructor(this);
  }
  return this;
}