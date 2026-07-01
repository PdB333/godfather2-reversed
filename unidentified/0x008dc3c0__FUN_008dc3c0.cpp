// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x008dc180
  BaseClass::constructor();
  
  // If the low bit of flags is set, allocate additional memory (0x210 bytes)
  if ((flags & 1) != 0) {
    operatorNew(this, 0x210); // FUN_0043b960 likely operator new or placement new
  }
  
  return this;
}