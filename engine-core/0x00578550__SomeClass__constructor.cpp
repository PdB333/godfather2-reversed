// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x00578570
  BaseClass::constructor();
  
  // If the low bit of flags is set, call the destructor (placement delete) at 0x009c8eb0
  if ((flags & 1) != 0) {
    operatorDelete(this);
  }
  
  return this;
}