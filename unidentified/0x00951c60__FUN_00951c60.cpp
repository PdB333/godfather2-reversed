// FUNC_NAME: SomeClass::destructor
undefined4 __thiscall SomeClass::destructor(undefined4 this, byte flags)
{
  // Call base destructor or cleanup function
  FUN_009513e0();
  
  // If the 'delete' flag is set (bit 0), free the memory
  if ((flags & 1) != 0) {
    // operator delete or custom deallocation
    FUN_005c4480(this);
  }
  
  return this;
}