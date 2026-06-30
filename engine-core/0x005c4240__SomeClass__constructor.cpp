// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte flags)
{
  *this = &PTR_FUN_00e3edf0;  // Set vtable pointer
  FUN_005d48a0();              // Base class constructor call
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);        // Destructor call if flag bit 0 is set (placement new cleanup)
  }
  return this;
}