// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flags)
{
  // Call base class constructor at 0x008223d0
  BaseClass::constructor(this);
  
  // If the low bit of flags is set, call a cleanup/destructor-like function
  if ((flags & 1) != 0) {
    SomeClass::cleanup(this); // FUN_009c8eb0 - likely frees internal resources
  }
  
  return this;
}