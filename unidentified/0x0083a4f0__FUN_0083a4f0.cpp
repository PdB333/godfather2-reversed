// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte flags)
{
  // Set vtable pointer (0x00d73ff8)
  *this = &PTR_FUN_00d73ff8;
  // Call base class initializer or common initialization
  FUN_004149b0();
  // If flags has bit 0 set, call destructor/deallocation (likely for cleanup on failure)
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  return this;
}