// FUNC_NAME: FUN_008a24c0 (constructor)
undefined4 * __thiscall FUN_008a24c0(undefined4 *this, byte flags)
{
  // Set vtable pointer to the class's vtable
  *this = &PTR_FUN_00d79048;  // +0x00: vtable pointer
  
  // Set some other class-specific pointer
  this[1] = &PTR_LAB_00d79040;  // +0x04: some other data pointer

  // Call base class constructor or initialization
  FUN_004bee40();

  // If the low bit of flags is set, call a destructor-like function
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }

  return this;
}