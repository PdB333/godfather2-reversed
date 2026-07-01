// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x008d3c00
  FUN_008d3c00();
  
  // If bit 0 of flags is set, call the parent destructor? (FUN_009c8eb0)
  // This pattern suggests this is a constructor that might need cleanup if the
  // construction fails, or it could be calling a parent constructor with flags.
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);  // This appears to be a destructor or cleanup function
  }
  
  return this;
}