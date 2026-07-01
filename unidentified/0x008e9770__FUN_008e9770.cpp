// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x008e9420
  FUN_008e9420();
  
  // If the low bit of flags is set, call operator delete (or a deallocation function)
  // at 0x0043b960 with size 0x1b0 (432 bytes)
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 0x1b0);
  }
  
  return this;
}