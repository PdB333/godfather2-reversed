// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)

{
  // Call base class constructor at 0x0086ccf0
  BaseClass::constructor();
  
  // If the low bit of flags is set, call operator delete (or similar cleanup) at 0x0043b960
  // with size 0xCC (204 bytes) - this is likely a placement delete or custom deallocation
  if ((flags & 1) != 0) {
    operatorDelete(this, 0xcc);
  }
  
  return this;
}