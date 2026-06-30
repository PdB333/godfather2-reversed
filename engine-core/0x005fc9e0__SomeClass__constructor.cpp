// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flags)
{
  // Call base class constructor
  baseConstructor();

  // If the lowest bit of flags is set, perform additional initialization
  if ((flags & 1) != 0) {
    additionalInit(this);
  }

  return this;
}