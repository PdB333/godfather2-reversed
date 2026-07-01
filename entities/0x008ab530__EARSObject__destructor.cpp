// FUNC_NAME: EARSObject::destructor
undefined4 * __thiscall EARSObject::destructor(undefined4 *this, byte flags)
{
  // Check if the object's data pointer (at +0x10) is non-null
  if (this[4] != 0) {
    // Call the virtual destructor function stored at +0x1C (this[7])
    (*(code *)this[7])(this[4]);
  }
  // Set the vtable pointer to the base class vtable (at 0x00e317cc)
  *this = &PTR_LAB_00e317cc;
  // If the low bit of flags is set, free the memory (operator delete)
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  return this;
}