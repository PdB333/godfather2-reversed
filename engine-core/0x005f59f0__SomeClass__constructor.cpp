// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte flags)
{
  // Set vtable pointer to first vtable
  *this = &PTR_FUN_00e40788;
  // Set second vtable pointer
  this[1] = &PTR_LAB_00e4078c;
  
  // Call base class constructor or initialization
  FUN_004086d0(&DAT_012069c4);
  FUN_004083d0();
  
  // Update vtable pointer to final vtable
  *this = &PTR_LAB_00e4079c;
  
  // Initialize some global flag to 0
  _DAT_0122351c = 0;
  
  // If flag bit 0 is set, call destructor or cleanup
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}