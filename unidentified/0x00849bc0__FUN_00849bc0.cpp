// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flags)

{
  // Call base class constructor at 0x00849980
  BaseClass::constructor();
  
  // If the lowest bit of flags is set, call the destructor at 0x009c8eb0
  if ((flags & 1) != 0) {
    SomeClass::destructor(this);
  }
  
  return (undefined4)this;
}