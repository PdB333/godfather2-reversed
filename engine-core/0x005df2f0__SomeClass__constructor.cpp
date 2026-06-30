// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte flags)
{
  // Set vtable pointer to class-specific VMT
  *this = &PTR_FUN_00e3f2d0;
  // Call base class initialization (likely constructor or init routine)
  FUN_004de130();
  // If bit 0 of flags is set, perform cleanup/destruction (e.g., deallocation)
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  return this;
}