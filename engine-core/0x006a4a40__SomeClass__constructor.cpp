// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flags)
{
  // Call base class constructor at 0x006a48d0
  BaseClass::constructor();
  
  // If the low bit of flags is set, call a cleanup/destructor-like function with size 100
  if ((flags & 1) != 0) {
    operator delete(this, 100);
  }
  
  return this;
}