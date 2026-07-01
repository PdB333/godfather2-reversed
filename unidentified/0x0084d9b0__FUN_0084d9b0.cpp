// FUNC_NAME: SomeClass::destructor
undefined4 * __thiscall SomeClass_destructor(undefined4 *this, byte flags)
{
  // Check if the second vtable-like pointer is non-null
  if (this[1] != 0) {
    // Call a cleanup function on the sub-object at offset +4
    FUN_004daf90(this + 1);
  }
  // Set the vtable pointer to the static vtable address
  *this = &PTR_LAB_00e2f0c0;
  // If the low bit of flags is set, deallocate the memory
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  return this;
}