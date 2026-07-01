// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flags)
{
  // Call base class constructor at 0x009031c0
  SomeClass_base::constructor(this);
  
  // If the low bit of flags is set, call operator delete (or similar deallocation) with size 0xA4
  if ((flags & 1) != 0) {
    operatorDelete(this, 0xa4); // FUN_0043b960 likely operator delete(void*, size_t)
  }
  
  return this;
}