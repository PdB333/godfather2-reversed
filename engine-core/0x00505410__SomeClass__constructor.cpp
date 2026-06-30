// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor or initializer
  SomeClass::baseConstructor();
  
  // If the low bit of flags is set, call the destructor or cleanup function
  if ((flags & 1) != 0) {
    SomeClass::destructorOrCleanup(this);
  }
  
  return this;
}