// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x00925550
  BaseClass::constructor();
  
  // If the low bit of flags is set, call the destructor at 0x005c4480
  // This is a common pattern for placement new with a flag indicating
  // whether to call the destructor on failure
  if ((flags & 1) != 0) {
    SomeClass::destructor(this);
  }
  
  return this;
}