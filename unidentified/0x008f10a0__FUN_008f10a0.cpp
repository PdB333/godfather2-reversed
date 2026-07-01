// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x008f0ff0
  FUN_008f0ff0();
  
  // If bit 0 of flags is set, call operator delete (or similar deallocation) at 0x0043b960
  // with size 0x60 (96 bytes) - likely freeing a sub-object or performing cleanup
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 0x60);
  }
  
  return this;
}