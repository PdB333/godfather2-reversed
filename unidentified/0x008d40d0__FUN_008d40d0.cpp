// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flags)
{
  // Call base class constructor at 0x008d4070
  FUN_008d4070(this);
  
  // If the low bit of flags is set, call a destructor-like function (placement delete?)
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return (undefined4)this;
}