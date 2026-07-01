// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x00813400
  BaseClass::constructor();
  
  // If the low bit of flags is set, call operator delete (or similar deallocation) at 0x0043b960
  // with size 0x68 (104 bytes) - likely freeing a sub-object or performing cleanup
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 0x68); // operator delete(this, 0x68) or similar deallocation
  }
  
  return this;
}