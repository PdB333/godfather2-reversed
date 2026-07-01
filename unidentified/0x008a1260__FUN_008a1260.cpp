// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x008a0b80
  FUN_008a0b80();
  
  // If bit 0 of flags is set, allocate 0x200 bytes (likely a buffer or array)
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 0x200);
  }
  
  return this;
}