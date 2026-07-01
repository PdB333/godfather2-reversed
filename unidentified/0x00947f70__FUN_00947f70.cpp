// FUNC_NAME: SomeClass::constructor
int __thiscall SomeClass::constructor(int this, byte flags)
{
  // Set vtable pointer at offset +0x18
  *(undefined ***)(this + 0x18) = &PTR_LAB_00e355fc;
  
  // Call base class constructor or initialization
  FUN_0064d150();
  
  // If flag bit 0 is set, call destructor or cleanup
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}