// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte flags)
{
  // Set vtable pointer
  *this = &PTR_FUN_00d7c2d8;
  
  // Call base class constructor(s) or initialization
  FUN_004086d0(&DAT_012069d4);
  FUN_004083d0();
  
  // If flag bit 0 is set, call destructor (placement delete)
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}