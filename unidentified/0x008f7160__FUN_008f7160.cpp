// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte flags)
{
  // Set vtable pointer to first vtable
  *this = &PTR_FUN_00d81218;
  
  // Call some initialization functions on global data
  FUN_00408310(&DAT_0112fe5c);
  FUN_00408310(&DAT_0112fe54);
  
  // Call another initialization function
  FUN_008f6fa0();
  
  // Update vtable pointer to second vtable (likely derived class or state change)
  *this = &PTR_LAB_00d81214;
  
  // Set global flag to 0
  DAT_0112a580 = 0;
  
  // If the low bit of flags is set, call destructor-like cleanup
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}