// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte flags)
{
  // Set vtable pointer to first vtable (likely base class)
  *this = &PTR_LAB_00d6f648;
  
  // Call some initialization function with parameter 0x25
  FUN_007f6420(0x25);
  
  // Set vtable pointer to second vtable (likely derived class)
  *this = &PTR_LAB_00d6b95c;
  
  // Call another initialization function
  FUN_0080ea60();
  
  // If the low bit of flags is set, call destructor-like function
  if ((flags & 1) != 0) {
    FUN_00624da0(this);
  }
  
  return this;
}