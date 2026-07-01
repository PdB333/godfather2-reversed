//FUNC_NAME: SomeClass::SomeClass
undefined4 __thiscall SomeClass::SomeClass(SomeClass *this, byte flags)
{
  // Call base class constructor or initializer (likely takes this implicitly)
  FUN_007c2ee0();
  
  // If the low bit of flags is set, call cleanup/destructor (e.g., operator delete)
  if ((flags & 1) != 0) {
    FUN_00624da0(this);
  }
  
  return this;
}