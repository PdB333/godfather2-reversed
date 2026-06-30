// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x006a9080
  SomeBaseClass::constructor();
  
  // If the low bit of flags is set, call the destructor at 0x009c8eb0
  // This is a common pattern for placement new / operator delete cleanup
  if ((flags & 1) != 0) {
    SomeClass::destructor(this);
  }
  
  return this;
}