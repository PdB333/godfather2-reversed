// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor twice? Possibly a bug or two separate initializations
  FUN_00900430(); // BaseClass::constructor
  FUN_00900430(); // BaseClass::constructor (duplicate call)
  
  // If bit 0 of flags is set, call additional initialization
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this); // SomeClass::initExtra
  }
  
  return this;
}