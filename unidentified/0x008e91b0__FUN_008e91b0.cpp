// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flags)

{
  // Call base class constructor at 0x008e9000
  BaseClass::constructor(this);
  
  // If the lowest bit of flags is set, allocate additional memory (0xB8 bytes)
  if ((flags & 1) != 0) {
    operatorNew(this, 0xb8); // FUN_0043b960 likely operator new or placement new
  }
  
  return this;
}