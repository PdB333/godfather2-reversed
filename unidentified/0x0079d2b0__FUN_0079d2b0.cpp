// FUNC_NAME: SomeClass::destructor
undefined4 * __thiscall SomeClass::destructor(undefined4 *this, byte flags)
{
  // Check if the pointer at offset +0x0C (3rd dword) is non-null and free it
  if (this[3] != 0) {
    FUN_004daf90(this + 3);
  }
  // Check if the pointer at offset +0x04 (1st dword) is non-null and free it
  if (this[1] != 0) {
    FUN_004daf90(this + 1);
  }
  // Set the vtable pointer to the static destructor sentinel (LAB_00e2f0c0)
  *this = &PTR_LAB_00e2f0c0;
  // If the destruction flags indicate operator delete should be called,
  // free the memory via FUN_009c8eb0 (likely operator delete or custom deallocator)
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  return this;
}