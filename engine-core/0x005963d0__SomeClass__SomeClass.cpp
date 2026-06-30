// FUNC_NAME: SomeClass::SomeClass
undefined4 * __thiscall SomeClass::SomeClass(SomeClass *this, byte flags)
{
  // Set vtable pointer (0x00e3adf0)
  *this = &PTR_FUN_00e3adf0;
  // Call base class constructor
  BaseClass::BaseClass();
  // If the lowest bit of flags is set, perform additional cleanup/initialization
  if ((flags & 1) != 0) {
    SomeClass::cleanup(this);
  }
  return this;
}