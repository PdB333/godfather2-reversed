// FUNC_NAME: SomeClass::destructor
undefined4 * __thiscall SomeClass::destructor(undefined4 *this, byte flags)
{
  // +0x0C: some pointer member
  if (this[3] != 0) {
    // Free/release resource at offset +0x0C
    FUN_004daf90(this + 3);
  }
  // +0x04: another pointer member
  if (this[1] != 0) {
    // Free/release resource at offset +0x04
    FUN_004daf90(this + 1);
  }
  // Set vtable pointer to base class destructor vtable
  *this = &PTR_LAB_00e2f0c0;
  // If bit 0 of flags is set, also call operator delete
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  return this;
}