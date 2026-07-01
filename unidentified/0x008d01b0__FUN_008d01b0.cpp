// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x008cfc40
  FUN_008cfc40();
  
  // If bit 0 of flags is set, call operator new with size 100 (0x64)
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 100); // Likely operator new or placement new
  }
  
  return this;
}