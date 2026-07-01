// FUNC_NAME: SomeClass::SomeClass
undefined4 * __thiscall SomeClass::SomeClass(undefined4 *this, byte flags)
{
  // Call base class constructor
  FUN_00407430();
  // Set vtable pointer (vtable at +0x00)
  *this = &PTR_LAB_00e317cc;
  // If flags bit 0 is set, call cleanup/destructor (likely operator delete)
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  return this;
}