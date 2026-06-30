// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte flags)
{
  // Set vtable pointer
  *this = &PTR_FUN_00e3edf0;  // vtable for SomeClass
  
  // Call base class constructor or initialization function
  FUN_005d48a0();  // likely base class constructor or init
  
  // If flag bit 0 is set, call destructor or cleanup
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);  // likely operator delete or destructor
  }
  
  return this;
}