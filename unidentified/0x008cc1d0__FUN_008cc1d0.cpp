// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte flags)
{
  *this = &PTR_FUN_00d7c3d0; // vtable setup
  FUN_00415130(); // base class constructor call
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this); // conditional cleanup/destruction
  }
  return this;
}