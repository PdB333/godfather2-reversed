// FUNC_NAME: SomeEarsClass::SomeEarsClass
undefined4 * __thiscall SomeEarsClass::SomeEarsClass(undefined4 *this, byte flags)
{
  // Set initial vtable pointer
  *this = &PTR_FUN_00d7b3a4;
  // Set second vtable pointer (likely from a base class)
  this[1] = &PTR_LAB_00d7b3a0;
  // Call a registration/hash function (0x8d946a1b is likely a type ID)
  FUN_004639e0(0x8d946a1b);
  // Override second vtable pointer again
  this[1] = &PTR_LAB_00d7b39c;
  // Set global flag to 0
  DAT_011299cc = 0;
  // Set main vtable to final class vtable
  *this = &PTR_LAB_00e30fe0;
  // If bit 0 of flags is set, call destructor (placement delete)
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  return this;
}