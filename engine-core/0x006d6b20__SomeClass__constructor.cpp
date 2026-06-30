// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)

{
  // Call base class constructor at 0x006d6490
  SomeClass::baseConstructor();

  // If the low bit of flags is set, call operator delete with size 0xf4
  if ((flags & 1) != 0) {
    operatorDelete(this, 0xf4);
  }

  return this;
}