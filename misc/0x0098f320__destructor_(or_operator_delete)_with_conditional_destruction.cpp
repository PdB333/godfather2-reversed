// FUNC_NAME: destructor (or operator delete) with conditional destruction
undefined4 * __thiscall unknownDestructor(undefined4 *this, byte flags)

{
  // Set vtable pointer (likely to base class destructor vtable)
  *this = &PTR_FUN_00d91b04;
  
  // Call base class destructor
  FUN_004de130();
  
  // If the 'free memory' flag (bit 0) is set, deallocate the object
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this); // operator delete / free
  }
  
  return this;
}