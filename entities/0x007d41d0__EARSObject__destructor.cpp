// FUNC_NAME: EARSObject::destructor
undefined4 * __thiscall EARSObject_destructor(undefined4 *this, byte flags)
{
  // Check if the secondary data pointer (offset +0x04) is non-null
  if (this[1] != 0) {
    // Call the destructor for the secondary data at this+4
    FUN_004daf90(this + 1);
  }
  // Set the vtable pointer to the base class vtable (offset +0x00)
  *this = &PTR_LAB_00e2f0c0;
  // If the low bit of flags is set, free the memory (operator delete)
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  return this;
}