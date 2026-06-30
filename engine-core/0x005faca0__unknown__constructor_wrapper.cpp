// FUNC_NAME: unknown::constructor_wrapper
undefined4 __thiscall FUN_005faca0(undefined4 this, byte flags)
{
  // Call base constructor or common initialization function
  FUN_005facc0();
  
  // If bit 0 of flags is set, call destructor or cleanup function
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}