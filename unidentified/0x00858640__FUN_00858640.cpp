// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte flags)
{
  // Set vtable pointer
  *this = &PTR_FUN_00d75318;
  
  // Call base class constructor
  FUN_008cef60();
  
  // If the low bit of flags is set, call destructor (placement delete)
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}